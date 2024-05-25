#include "functions.hpp"
#include "../functions.hpp"
#include "core/file/format/pe/defines.hpp"
#include "shared/value/AddressType.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <shared/RuntimeException.hpp>

IMAGE_DOS_HEADER* format::pe::dosHeader(CBinary* binary)
{
    format::assertBinaryNotNull(binary);

    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(binary->pointer(0).ptr());

    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		throw RuntimeException(strenc("Invalid IMAGE_DOS_SIGNATURE"));
    }

	return dosHeader;
}

IMAGE_NT_HEADERS32* format::pe::ntHeaders32(CBinary* binary)
{
    format::assertBinaryNotNull(binary);

	auto dosHeader = format::pe::dosHeader(binary);

    IMAGE_NT_HEADERS32* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS32*>(binary->pointer(dosHeader->e_lfanew).ptr());

    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
		throw RuntimeException(strenc("Invalid IMAGE_NT_SIGNATURE"));
    }

	return ntHeaders;
}

IMAGE_NT_HEADERS64* format::pe::ntHeaders64(CBinary* binary)
{
    format::assertBinaryNotNull(binary);

	auto dosHeader = format::pe::dosHeader(binary);

    IMAGE_NT_HEADERS64* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS64*>(binary->pointer(dosHeader->e_lfanew).ptr());

    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
		throw RuntimeException(strenc("Invalid IMAGE_NT_SIGNATURE"));
    }

	return ntHeaders;
}


uint_16 format::pe::numberOfSections(CBinary* binary, AddressType addressType)
{
    if (addressType == AddressType::_32_BIT) {
        return format::pe::ntHeaders32(binary)->FileHeader.NumberOfSections;
    } else if (addressType == AddressType::_64_BIT) {
	    return format::pe::ntHeaders64(binary)->FileHeader.NumberOfSections;
    } else {
        throw RuntimeException(strenc("Unknown address type!"));
    }
}

uint_32 format::pe::sectionsStartOffset(CBinary* binary, AddressType addressType)
{
    auto dosHeader = format::pe::dosHeader(binary);
    uint_32 sizeOfImageNtHeaders;

    if (addressType == AddressType::_32_BIT) {
        sizeOfImageNtHeaders = sizeof(IMAGE_NT_HEADERS32);
    } else if (addressType == AddressType::_64_BIT) {
        sizeOfImageNtHeaders = sizeof(IMAGE_NT_HEADERS64);
    } else {
        throw RuntimeException(strenc("Unknown address type!"));
    }

    return dosHeader->e_lfanew + sizeOfImageNtHeaders;
}

IMAGE_DATA_DIRECTORY* format::pe::imageDataDirectoryEntry(CBinary* binary, AddressType addressType, uint_16 entryType)
{
    if (addressType == AddressType::_32_BIT) {
        return &format::pe::ntHeaders32(binary)->OptionalHeader.DataDirectory[entryType];
    } else if (addressType == AddressType::_64_BIT) {
	    return &format::pe::ntHeaders64(binary)->OptionalHeader.DataDirectory[entryType];
    } else {
        throw RuntimeException(strenc("Unknown address type!"));
    }
}

