#ifndef CORE_FORMAT_PE_FUNCTIONS_HPP_
#define CORE_FORMAT_PE_FUNCTIONS_HPP_

#include "core/format/pe/PeFormat.hpp"
#include "core/shared/Binary.hpp"
#include "core/shared/SectionPermissions.hpp"
#include "defines.hpp"
#include "PeSection.hpp"
#include "PeModule.hpp"

namespace program::core::format::pe {
    IMAGE_DOS_HEADER* dosHeader(const program::core::shared::CBinary& binary);
    template <typename NT_HEADERS>
    NT_HEADERS* ntHeaders(const program::core::shared::CBinary& binary);
    IMAGE_NT_HEADERS32* ntHeaders32(const program::core::shared::CBinary& binary);
    IMAGE_NT_HEADERS64* ntHeaders64(const program::core::shared::CBinary& binary);
    uint_16 numberOfSections(const CPeFormat& peFormat);
    binary_offset sectionsStartOffset(const CPeFormat& peFormat);
    pe_section_vec readSectionList(const CPeFormat& peFormat);
    binary_offset rvaToOffset(const CPeFormat& peFormat, const binary_offset rva);
    IMAGE_DATA_DIRECTORY* imageDataDirectory(const CPeFormat& peFormat);
    template <typename IMAGE_THUNK_DATA, typename IMAGE_ORDINAL_FLAG>
    pe_import_vec readModuleImports(const CPeFormat& peFormat, const IMAGE_IMPORT_DESCRIPTOR* imageImportDescriptor, const IMAGE_ORDINAL_FLAG& imageOrdinalFlag);
    pe_module_map readImportModules(const CPeFormat& peFormat);
    uint_32 convertSectionPermissionsToCharacteristics(const program::core::shared::CSectionPermissions& permissions);
    program::core::shared::CSectionPermissions convertCharacteristicsToSectionPermissions(const uint_32 characteristics);
    IMAGE_SECTION_HEADER createNextSectionHeader(
        const uint_32 fileAlignment,
        const uint_32 sectionAlignment,
        const IMAGE_SECTION_HEADER& previousSectionHeader,
        const std::string& name,
        binary_offset size,
        const program::core::shared::CSectionPermissions permissions
    );
    CPeFormat addSection(
        const CPeFormat& peFormat,
        const std::string& name,
        binary_offset size,
        const program::core::shared::CSectionPermissions permissions
    );
}

#endif // CORE_FORMAT_PE_FUNCTIONS_HPP_
