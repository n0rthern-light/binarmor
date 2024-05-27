#pragma once

#include "core/file/format/pe/PeFormat.hpp"
#include "defines.hpp"
#include "../../Binary.hpp"
#include "PeSection.hpp"
#include "PeImport.hpp"

namespace format {
    namespace pe {
        IMAGE_DOS_HEADER* dosHeader(const CBinary* binary);
        IMAGE_NT_HEADERS32* ntHeaders32(const CBinary* binary);
        IMAGE_NT_HEADERS64* ntHeaders64(const CBinary* binary);
        uint_16 numberOfSections(const CPeFormat* peFormat);
        binary_offset sectionsStartOffset(const CPeFormat* peFormat);
        pe_section_vec readSectionList(const CPeFormat* peFormat);
        binary_offset rvaToOffset(const CPeFormat* peFormat, const binary_offset& rva);
        IMAGE_DATA_DIRECTORY* imageDataDirectory(const CPeFormat* peFormat);
        pe_import_vec readImportList(const CPeFormat* peFormat);
    };
}

