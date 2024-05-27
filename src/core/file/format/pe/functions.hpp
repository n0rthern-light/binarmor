#pragma once

#include "defines.hpp"
#include "shared/value/AddressType.hpp"
#include "../../Binary.hpp"
#include "PeSection.hpp"
#include "PeImport.hpp"

namespace format {
    namespace pe {
        IMAGE_DOS_HEADER* dosHeader(CBinary* binary);
        IMAGE_NT_HEADERS32* ntHeaders32(CBinary* binary);
        IMAGE_NT_HEADERS64* ntHeaders64(CBinary* binary);
        uint_16 numberOfSections(CBinary* binary, AddressType addressType);
        binary_offset sectionsStartOffset(CBinary* binary, AddressType addressType);
        pe_section_vec readSectionList(CBinary* binary, AddressType addressType);
        binary_offset rvaToOffset(CBinary* binary, AddressType addressType, binary_offset rva);
        IMAGE_DATA_DIRECTORY* imageDataDirectory(CBinary* binary, AddressType addressType);
        pe_import_vec readImportList(CBinary* binary, AddressType addressType);
    };
}

