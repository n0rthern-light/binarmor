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

byte_vec CNasmPayloadProcessor::produceDataBytes(format_ptr format, const Data_t& data) const
{
    if (format->endianness() != Endianness::LITTLE) {
        throw RuntimeException(strenc("Only LE byte order is supported"));
    }

    const auto parts = extractPartsOfData(data);

    if (parts.size() < 3) {
        throw RuntimeException(strenc("Invalid data entry"));
    }

    if (isStructData(data)) {
        
    } else {
        const auto& type = parts[1];
        const auto& value = parts[2];

        if (StringFunctions::endsWith(value, ",")) {
            // is array or string (still array)
            if (type != "db") {
                throw RuntimeException(strenc("Only db type in array supported"));
            }
        } else {
            // is immediate
            if (type == "db") {
                //byte
            } else if (type == "dw") {
                //word
            } else if (type == "dd") {
                //dword
            } else if (type == "dq") {
                //qword
                if (format->architecture() == Architecture::X86) {
                    throw RuntimeException(strenc("dq data type is not supported in 32 bit arch"));
                }
            } else {
                throw RuntimeException(std::format(strenc("{} is unknown data type in NasmPayloadProcessor"), type));
            }
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

    // then not dependant data
    // then not dependant code
    // then dependant things
    // the things with the most dependencies last

    return nullptr;
}
