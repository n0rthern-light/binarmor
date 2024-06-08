#ifndef SRC_CORE_FORMAT_PE_FUNCTIONS_HPP_
#define SRC_CORE_FORMAT_PE_FUNCTIONS_HPP_





#include "core/format/pe/PeFormat.hpp"
#include "defines.hpp"
#include "../../Binary.hpp"
#include "PeSection.hpp"
#include "PeModule.hpp"

namespace format {
    namespace pe {
        IMAGE_DOS_HEADER* dosHeader(const CBinary* binary);
        template <typename NT_HEADERS>
        NT_HEADERS* ntHeaders(const CBinary* binary);
        IMAGE_NT_HEADERS32* ntHeaders32(const CBinary* binary);
        IMAGE_NT_HEADERS64* ntHeaders64(const CBinary* binary);
        uint_16 numberOfSections(const CPeFormat* peFormat);
        binary_offset sectionsStartOffset(const CPeFormat* peFormat);
        pe_section_vec readSectionList(const CPeFormat* peFormat);
        binary_offset rvaToOffset(const CPeFormat* peFormat, const binary_offset& rva);
        IMAGE_DATA_DIRECTORY* imageDataDirectory(const CPeFormat* peFormat);
        template <typename IMAGE_THUNK_DATA, typename IMAGE_ORDINAL_FLAG>
        pe_import_vec readModuleImports(const CPeFormat* peFormat, const IMAGE_IMPORT_DESCRIPTOR* imageImportDescriptor, const IMAGE_ORDINAL_FLAG& imageOrdinalFlag);
        pe_module_map readImportModules(const CPeFormat* peFormat);
    };
}




#endif // SRC_CORE_FORMAT_PE_FUNCTIONS_HPP_
