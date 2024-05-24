#pragma once

#include "defines.hpp"
#include "../../Binary.hpp"
#include "shared/value/AddressType.hpp"

namespace format {
    namespace pe {
        IMAGE_DOS_HEADER* dosHeader(CBinary* binary);
        IMAGE_NT_HEADERS32* ntHeaders32(CBinary* binary);
        IMAGE_NT_HEADERS64* ntHeaders64(CBinary* binary);
        uint16_t numberOfSections(CBinary* binary, AddressType addressType);
        uint32_t sectionsStartOffset(CBinary* binary, AddressType addressType);
        IMAGE_DATA_DIRECTORY* imageDataDirectoryEntry(CBinary* binary, AddressType addressType, size_t entryType);
    };
}

