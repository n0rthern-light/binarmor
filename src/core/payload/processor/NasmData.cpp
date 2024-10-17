#include "NasmData.hpp"
#include "core/payload/defines.hpp"
#include "shared/string/StringFunctions.hpp"
#include "shared/value/ByteVecOperations.hpp"
#include "shared/value/Unsigned.hpp"

using namespace program::core::payload;
using namespace program::core::payload::nasm;
using namespace program::core::shared;
using namespace program::shared;
using namespace program::shared::types;
using namespace program::shared::value;
using namespace program::shared::string;

bool CNasmData::isImmediateValue(const std::string& value) const
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

CNasmData::CNasmData(const std::string& sectionName, const Data_t& data):
    m_sectionName(sectionName),
    m_data(data)
{ }

CNasmData::CNasmData(const CNasmData& other):
    m_sectionName(other.m_sectionName),
    m_data(other.m_data)
{ }

CNasmData CNasmData::operator=(const CNasmData& other)
{
    if (this != &other) {
        return CNasmData { other };
    }

    return *this;
}

std::string CNasmData::sectionName() const
{
    return m_sectionName;
}

std::vector<std::string> CNasmData::extractParts() const
{
    return StringFunctions::splitByCharacter(m_data.definition, ' ');
}

std::string CNasmData::dataLabel() const
{
    const auto parts = extractParts();
    return StringFunctions::replaceAll(parts[0], ":", "");
}

data_id CNasmData::dataId(const std::string& payloadPrefix) const
{
    return std::format(strenc("data:{}:{}:{}"), m_sectionName, payloadPrefix, dataLabel());
}

bool CNasmData::isValidType(const std::string& type) const
{
    return type == "db" || type == "dw" || type == "dd" || type == "dq";
}

byte_vec CNasmData::produceDataBytes(Endianness endianness, Architecture architecture) const
{
    if (endianness != Endianness::LITTLE) {
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
            if (architecture == Architecture::X86) {
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

    const auto parts = extractParts();

    if (parts.size() < 3) {
        throw RuntimeException(strenc("Invalid data entry"));
    }

    if (isStructData()) {
        auto bytes = byte_vec { };
        for(size_t i = 1; i < parts.size() - 1; ++i) {
            const auto& type = parts[i];
            auto values = std::vector<std::string> { };


            while(isValidType(parts[i + 1]) == false && i < parts.size() - 1) {
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

std::vector<std::string> CNasmData::dependencies() const
{
    const auto parts = extractParts();
    auto dependencies = std::vector<std::string> { };

    if (isStructData()) {
        for(size_t i = 1; i < parts.size() - 1; ++i) {
            const auto& type = parts[i];
            const auto& val = parts[i+1];

            while (StringFunctions::endsWith(parts[i+1], ",") && i < parts.size() - 1) {
                // adjust if byte array
                ++i;
            }

            if (isImmediateValue(val) == false && (type == "dd" || type == "dq")) {
                dependencies.push_back(val);
            }
        }
    } else {
        if (parts.size() != 3) {
            return dependencies;
        }

        const auto& val = parts[2];

        if (isImmediateValue(val) == true) {
            return dependencies;
        }

        dependencies.push_back(val);
    }

    return dependencies;
}

CNasmData CNasmData::resolveDependency(const std::string& dependency, binary_offset dependencyOffset) const
{
    const auto& definition = m_data.definition;
    const auto offset = CUnsigned{ (uint_64)dependencyOffset };
    const auto newDefinition = StringFunctions::replaceAll(definition, dependency, offset.asShortHexString());

    const auto newData = Data_t {
        newDefinition
    };

    return CNasmData { m_sectionName, newData };
}

bool CNasmData::isStructData() const
{
    const auto parts = extractParts();

    if (parts.size() < 3) {
        return false;
    }

    return parts[0].back() == ':';
}


