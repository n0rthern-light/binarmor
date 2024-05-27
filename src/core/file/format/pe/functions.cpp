#include "functions.hpp"
#include "../functions.hpp"
#include "core/file/format/pe/defines.hpp"
#include "shared/value/AddressType.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <shared/RuntimeException.hpp>
#include <stdio.h>

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

binary_offset format::pe::sectionsStartOffset(CBinary* binary, AddressType addressType)
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

pe_section_vec format::pe::readSectionList(CBinary* binary, AddressType addressType)
{
	auto vec = pe_section_vec();

	auto numberOfSections = format::pe::numberOfSections(binary, addressType);
    auto offset = format::pe::sectionsStartOffset(binary, addressType);

	auto binaryPointer = binary->pointer(offset);
    for(int i = 0; i < numberOfSections; ++i)
    {
        auto sectionOrigin = binaryPointer.shift(i * sizeof(IMAGE_SECTION_HEADER));
        auto sectionHeader = *reinterpret_cast<IMAGE_SECTION_HEADER*>(sectionOrigin.ptr());
        auto section = std::make_shared<CPeSection>(sectionHeader);
        vec.push_back(section);
    }

	return vec;
}

binary_offset format::pe::rvaToOffset(CBinary* binary, AddressType addressType, binary_offset rva)
{
    auto sections = format::pe::readSectionList(binary, addressType);

    for(auto section : sections) {
        auto virtualAddress = section->virtualAddress().get();

        if (virtualAddress > rva) {
            continue;
        }

        auto virtualSize = section->virtualSize();

        if (virtualAddress + virtualSize < rva) {
            continue;
        }
        auto rawAddress = section->rawAddress().get();
        binary_offset offset = rva - virtualAddress + rawAddress;

        if (offset < rawAddress || offset >= (rawAddress + section->rawSize())) {
            throw RuntimeException(strenc("Converted Raw Offset seems to be invalid"));
        }

        return offset;
    }

    throw RuntimeException(strenc("Could not convert RVA to Raw Offset"));
}

IMAGE_DATA_DIRECTORY* format::pe::imageDataDirectory(CBinary* binary, AddressType addressType)
{
    if (addressType == AddressType::_32_BIT) {
        return format::pe::ntHeaders32(binary)->OptionalHeader.DataDirectory;
    } else if (addressType == AddressType::_64_BIT) {
	    return format::pe::ntHeaders64(binary)->OptionalHeader.DataDirectory;
    } else {
        throw RuntimeException(strenc("Unknown address type!"));
    }
}

pe_import_vec format::pe::readImportList(CBinary* binary, AddressType addressType)
{

    pe_import_vec vec{ };

    auto importDataDirectory = format::pe::imageDataDirectory(binary, addressType)[IMAGE_DIRECTORY_ENTRY_IMPORT];
    auto importDescriptorPtr = binary->pointer(format::pe::rvaToOffset(binary, addressType, importDataDirectory.VirtualAddress));
    auto importDescriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(importDescriptorPtr.ptr());

    while (importDescriptor->Name != 0) {
        auto dllName = binary->string(format::pe::rvaToOffset(binary, addressType, importDescriptor->Name));



        importDescriptor++;
    }

    return vec;

    /*
    auto importDescriptorPtr = binary->pointer(dataDirectory.VirtualAddress);
    auto importDescriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(importDescriptorPtr.ptr());

    //auto dllName = binary->string(importDescriptor->Name);

    auto importDescriptorPtr = binary->pointer(dataDirectory.VirtualAddress);
    auto importDescriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(importDescriptorPtr.ptr());

    while(importDescriptor->OriginalFirstThunk && importDescriptor->FirstThunk && binary->offsetExists(importDescriptor->OriginalFirstThunk) && binary->offsetExists(importDescriptor->FirstThunk)) {
        auto dllName = binary->string(importDescriptor->Name);

        ++importDescriptor;
    }
    */


        /*
    while (importDescriptor->Name != 0 && currentOffset < dataDirectory->Size) {
        auto dllName = binary->string(importDescriptor->Name);

        if (addressType == AddressType::_64_BIT) {
            auto originalFirstThunk = reinterpret_cast<IMAGE_THUNK_DATA64*>(binary->pointer(importDescriptor->OriginalFirstThunk).ptr());
            auto firstThunk = reinterpret_cast<IMAGE_THUNK_DATA64*>(binary->pointer(importDescriptor->FirstThunk).ptr());

            while(originalFirstThunk->u1.AddressOfData != 0) {
                pe_import_ptr import = nullptr;
                if (originalFirstThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG64) {
                    import = std::make_shared<CPeImport>(
                        dllName,
                        strenc("Ordinal"),
                        0,
                        originalFirstThunk->u1.Ordinal & 0xFFFF
                    );
                } else {
                    auto importByName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(binary->pointer(originalFirstThunk->u1.AddressOfData).ptr());

                    import = std::make_shared<CPeImport>(
                        dllName,
                        std::string(importByName->Name),
                        importByName->Hint,
                        0
                    );
                }

                vec.push_back(import);
                originalFirstThunk++;
                firstThunk++;
            }
        } else {
            auto originalFirstThunk = reinterpret_cast<IMAGE_THUNK_DATA32*>(binary->pointer(importDescriptor->OriginalFirstThunk).ptr());
            auto firstThunk = reinterpret_cast<IMAGE_THUNK_DATA32*>(binary->pointer(importDescriptor->FirstThunk).ptr());

            while(originalFirstThunk->u1.AddressOfData != 0) {
                pe_import_ptr import = nullptr;
                if (originalFirstThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG32) {
                    import = std::make_shared<CPeImport>(
                        dllName,
                        strenc("Ordinal"),
                        0,
                        originalFirstThunk->u1.Ordinal & 0xFFFF
                    );
                } else {
                    auto importByName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(binary->pointer(originalFirstThunk->u1.AddressOfData).ptr());

                    import = std::make_shared<CPeImport>(
                        dllName,
                        std::string(importByName->Name),
                        importByName->Hint,
                        0
                    );
                }

                vec.push_back(import);
                originalFirstThunk++;
                firstThunk++;
            }
        }

        importDescriptor++;
    }
        */

    return vec;
}

