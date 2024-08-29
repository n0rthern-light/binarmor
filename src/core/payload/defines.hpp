#pragma once

#include "core/assembler/defines.hpp"
#include "core/shared/Binary.hpp"
#include "shared/types/defines.hpp"
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace program
{
    namespace core
    {
        namespace payload
        {
            struct ImportRequirement_t
            {
                const std::string moduleName;
                const std::string functionName;
            };

            using data_id = std::string;
            enum class DataResolveType
            {
                OFFSET = 0,
                VALUE = 1,
            };
            struct Data_t
            {
                const std::string definition;
            };
            struct SectionData_t
            {
                const std::string sectionName;
                const std::vector<const Data_t> data;
            };

            struct ImportResolved_t
            {
                const binary_offset address;
            };

            using import_ref = ImportRequirement_t;
            using resolved_import_map = std::map<import_ref, ImportResolved_t>;

            struct DataResolved_t
            {
                const binary_offset address;
                const std::optional<CBinary> value = std::nullopt;
            };

            using resolved_data_map = std::map<data_id, DataResolved_t>;

            using procedure_id = std::string;
            struct Procedure_t
            {
                const procedure_id procedureId;
                const program::core::assembler::asm_instructions code;
            };
            struct SectionProcedures_t
            {
                const std::string sectionName;
                const std::vector<const Procedure_t> procedures;
            };

            struct ResolvedProcedure_t
            {
                const procedure_id procedureId;
                const binary_offset address;
            };

            using resolved_procedure_map = std::map<procedure_id, ResolvedProcedure_t>;

            enum class DataType
            {
                DB = 0, // byte (1b) 8bit
                DW = 1, // word (2b) 16bit
                DD = 2, // doubleword (4b) 32bit
                DQ = 3 // quadword (8b) 64bit
            };

            struct DataToInitialize_t
            {
                const data_id id;
                const byte_vec bytes;
                const DataType type;
            };

            struct ResolvedContext_t
            {
                const resolved_import_map importMap;
                const resolved_data_map dataMap;
                const resolved_procedure_map procedureMap;
            };
        }
    }
}

