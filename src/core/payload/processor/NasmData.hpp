#pragma once

#include "core/payload/defines.hpp"
#include "core/shared/attributes.hpp"
#include "shared/types/defines.hpp"
#include <string>

namespace program::core::payload::nasm
{
    class CNasmData
    {
        const std::string m_sectionName;
        const Data_t m_data;

        bool isImmediateValue(const std::string& value) const;
    public:
        CNasmData(const std::string& sectionName, const Data_t& data);
        CNasmData(const CNasmData& other);
        CNasmData operator=(const CNasmData& other);
        std::string sectionName() const;
        std::vector<std::string> extractParts() const;
        std::string dataLabel() const;
        data_id dataId(const std::string& payloadPrefix) const;
        bool isValidType(const std::string& type) const;
        byte_vec produceDataBytes(program::core::shared::Endianness endianness, program::core::shared::Architecture architecture) const;
        std::vector<std::string> dependencies() const;
        CNasmData resolveDependency(const std::string& dependency, binary_offset dependencyOffset) const;
        bool isStructData() const;
    };
}
