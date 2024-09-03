#include "core/payload/processor/NasmPayloadProcessor.hpp"
#include "core/file/BinaryFile.hpp"
#include "core/format/IFormat.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "core/modification/AddImportCommand.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "core/shared/attributes.hpp"
#include "shared/RuntimeException.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include "shared/string/StringFunctions.hpp"
#include "shared/value/ByteVecOperations.hpp"
#include <cassert>
#include <format>
#include <memory>
#include <stdexcept>
#include <string>

CNasmPayloadProcessor::CNasmPayloadProcessor(CBinaryFileStateManager* fileManager): m_fileManager(fileManager) { assert(fileManager != nullptr); }

bool CNasmPayloadProcessor::isImmediateValue(const std::string& value) const
{
    const auto trimmedValue = StringFunctions::trim(value);

    if (
        StringFunctions::isDecValue(trimmedValue) ||
        StringFunctions::isHexValue(trimmedValue)
    ) {
        return true;
    }

    if (StringFunctions::endsWith(trimmedValue, ",")) {
        const auto clearedValue = StringFunctions::replaceAll(trimmedValue, ",", "");

        if (StringFunctions::isWrappedBy(value, "'", "'")) {
            // is string
            return true;
        }

        if (
            StringFunctions::isDecValue(clearedValue) ||
            StringFunctions::isHexValue(clearedValue)
        ) {
            // is byte arr
            return true;
        }
    }
    
    return false;
}

bool CNasmPayloadProcessor::isStructData(const Data_t& data) const
{
    const auto parts = extractPartsOfData(data);

    if (parts.size() < 3) {
        return false;
    }

    return parts[0].back() == ':';
}

bool CNasmPayloadProcessor::hasDependency(const Data_t& data) const
{
    const auto parts = extractPartsOfData(data);

    if (isStructData(data)) {
        for(size_t i = 1; i < parts.size() - 1; ++i) {
            const auto& type = parts[i];
            const auto& val = parts[i+1];

            while (StringFunctions::endsWith(parts[i+1], ",") && i < parts.size() - 1) {
                // adjust if byte array
                ++i;
            }

            if (isImmediateValue(val) == false && (type == "dd" || type == "dq")) {
                return true;
            }
        }

        return false;
    } else {
        if (parts.size() != 3) {
            return false;
        }

        const auto& val = parts[2];

        if (isImmediateValue(val) == true) {
            return false;
        }

        return true;
    }
}

std::vector<std::string> CNasmPayloadProcessor::extractPartsOfData(const Data_t& data) const
{
    return StringFunctions::splitByCharacter(data.definition, ' ');
}

std::string CNasmPayloadProcessor::dataLabel(const Data_t& data) const
{
    const auto parts = extractPartsOfData(data);
    return StringFunctions::replaceAll(parts[0], ":", "");
}

data_id CNasmPayloadProcessor::dataId(const IPayload* payload, const std::string sectionName, const std::string& dataLabel) const
{
    return std::format(strenc("data:{}:{}:{}"), sectionName, payload->id(), dataLabel);
}

bool CNasmPayloadProcessor::isValidTypeName(const std::string& str) const
{
    return str == "db" || str == "dw" || str == "dd" || str == "dq";
}

byte_vec CNasmPayloadProcessor::produceDataBytes(format_ptr format, const Data_t& data) const
{
    if (format->endianness() != Endianness::LITTLE) {
        throw RuntimeException(strenc("Only LE byte order is supported"));
    }

    const auto parseSingleValue = [&](const std::string& type, const std::string& value) -> byte_vec {
        if (type == "db") {
            return StringFunctions::convertToUnsigned(value).asLittleEndianBytes(1);
        } else if (type == "dw") {
            return StringFunctions::convertToUnsigned(value).asLittleEndianBytes(2);
        } else if (type == "dd") {
            return StringFunctions::convertToUnsigned(value).asLittleEndianBytes(4);
        } else if (type == "dq") {
            if (format->architecture() == Architecture::X86) {
                throw RuntimeException(strenc("dq data type is not supported in 32 bit arch"));
            }

            return StringFunctions::convertToUnsigned(value).asLittleEndianBytes(8);
        } else {
            throw RuntimeException(std::format(strenc("{} is unknown data type in NasmPayloadProcessor"), type));
        }
    };

    const auto parseSingleValueOfArray = [&](const std::string& value) -> byte_vec {
        if (StringFunctions::isWrappedBy(value, "'", "'")) {
            const auto stringContent = value.substr(1, value.length() - 1);

            return StringFunctions::convertToBytes(stringContent);
        } else if (StringFunctions::isDecValue(value) || StringFunctions::isHexValue(value)) {
            const auto unsignedValue = StringFunctions::convertToUnsigned(value);

            if (unsignedValue.get() > 0xFF) {
                throw RuntimeException(std::format(strenc("{} is too big value for being byte"), unsignedValue.get()));
            }

            auto byteVec = byte_vec { };
            byteVec.push_back(unsignedValue.get() & 0xFF);
            return byteVec;
        } else {
            throw RuntimeException(std::format(strenc("{} is unrecognizable type"), value));
        }
    };

    const auto parts = extractPartsOfData(data);

    if (parts.size() < 3) {
        throw RuntimeException(strenc("Invalid data entry"));
    }

    if (isStructData(data)) {
        auto bytes = byte_vec { };
        for(size_t i = 1; i < parts.size() - 1; ++i) {
            const auto& type = parts[i];
            auto values = std::vector<std::string> { };


            while(isValidTypeName(parts[i + 1]) == false && i < parts.size() - 1) {
                auto currentValue = parts[i + 1];
                if (StringFunctions::endsWith(currentValue, ",") == true) {
                    currentValue = StringFunctions::trimFromEnd(currentValue, 1);
                }

                values.push_back(currentValue);

                ++i;
            }

            if (values.size() == 1) {
                const auto& singleValue = values[0];
                bytes = CByteVecOperations::bytesAppendToEnd(bytes, parseSingleValue(type, singleValue));
            } else if (values.size() > 1) {
                if (type != "db") {
                    throw RuntimeException(strenc("Only db type in array supported"));
                }
                for(const auto& singleValue : values) {
                    bytes = CByteVecOperations::bytesAppendToEnd(bytes, parseSingleValueOfArray(singleValue));
                }
            } else {
                throw RuntimeException(strenc("Could not parse values array"));
            }
        }

        return bytes;
    } else {
        const auto& type = parts[1];
        const auto& value = parts[2];

        if (StringFunctions::endsWith(value, ",")) {
            if (type != "db") {
                throw RuntimeException(strenc("Only db type in array supported"));
            }

            if (parts.size() <= 3) {
                throw RuntimeException(strenc("Expected more parts when comma occurs"));
            }

            auto bytes = byte_vec { };
            for(size_t i = 2; i < parts.size(); ++i) {
                auto currentPart = parts[i];
                
                if (StringFunctions::endsWith(currentPart, ",")) {
                    currentPart = StringFunctions::trimFromEnd(currentPart, 1);
                }

                CByteVecOperations::bytesAppendToEnd(bytes, parseSingleValueOfArray(currentPart));
            }

            return bytes;
        } else {
            return parseSingleValue(type, value);
        }
    }
}

const std::shared_ptr<IModificationCommand> CNasmPayloadProcessor::next(const file_id& fileId, const IPayload* payload) const
{
    if (payload == nullptr) {
        throw RuntimeException(strenc("An actual payload must be provided"));
    }

    auto binaryFile = m_fileManager->binaryFile(fileId);

    if (binaryFile->format() != payload->format()) {
        throw RuntimeException(strenc("Payload and Binary format mismatch!"));
    }

    if (binaryFile->arch() != payload->architecture()) {
        throw RuntimeException(strenc("Payload and Binary architecture mismatch!"));
    }

    auto fileFormat = m_fileManager->binaryFileModifiedBinaryAsFormat(fileId);

    // imports are being processed always first
    for(const auto& requiredImport : payload->imports()) {
        const auto& import = fileFormat->import(requiredImport.moduleName, requiredImport.functionName);
        if (import == nullptr) {
            return std::make_shared<CAddImportCommand>(fileId, requiredImport.moduleName, requiredImport.functionName);
        }
    }

    const auto localData = std::vector<std::string> { };
    // then not dependant data
    for(const auto& section : payload->data()) {
        for(const auto& sectionData : section.data) {
            if (hasDependency(sectionData) == true) {
                continue;
            }

            const auto label = dataLabel(sectionData);
            const auto id = dataId(payload, section.sectionName, label);
            const auto bytesId = CUuid{ id };

            if (binaryFile->hasModification(bytesId)) {
                continue;
            }

            return std::make_shared<CAddBytesCommand>(
                fileId,
                bytesId,
                section.sectionName,
                produceDataBytes(fileFormat, sectionData),
                false,
                true,
                false
            );
        }
    }

    // then not dependant code
    for(const auto& sectionProcedures : payload->text()) {
        for(const auto& procedure : sectionProcedures.procedures) {
            for(const auto& instruction : procedure.instructions) {
                
            }
        }
    }

    // then dependant things
    // the things with the most dependencies last

    return nullptr;
}
