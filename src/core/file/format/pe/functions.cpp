#include "functions.hpp"
#include "../functions.hpp"
#include "core/file/format/pe/defines.hpp"
#include "shared/value/AddressType.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <shared/RuntimeException.hpp>
#include <stdio.h>

IMAGE_DOS_HEADER* format::pe::dosHeader(const CBinary* binary)
{
    format::assertBinaryNotNull(binary);

    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(binary->pointer(0).ptr());

    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		throw RuntimeException(strenc("Invalid IMAGE_DOS_SIGNATURE"));
    }

	return dosHeader;
}

IMAGE_NT_HEADERS32* format::pe::ntHeaders32(const CBinary* binary)
{
    format::assertBinaryNotNull(binary);

	auto dosHeader = format::pe::dosHeader(binary);

    IMAGE_NT_HEADERS32* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS32*>(binary->pointer(dosHeader->e_lfanew).ptr());

    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
		throw RuntimeException(strenc("Invalid IMAGE_NT_SIGNATURE"));
    }

	return ntHeaders;
}

IMAGE_NT_HEADERS64* format::pe::ntHeaders64(const CBinary* binary)
{
    format::assertBinaryNotNull(binary);

	auto dosHeader = format::pe::dosHeader(binary);

    IMAGE_NT_HEADERS64* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS64*>(binary->pointer(dosHeader->e_lfanew).ptr());

    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
		throw RuntimeException(strenc("Invalid IMAGE_NT_SIGNATURE"));
    }

	return ntHeaders;
}


uint_16 format::pe::numberOfSections(const CPeFormat* peFormat)
{
    auto binary = peFormat->binary();
    auto addressType = peFormat->addressType();

    if (addressType == AddressType::_32_BIT) {
        return format::pe::ntHeaders32(binary)->FileHeader.NumberOfSections;
    } else if (addressType == AddressType::_64_BIT) {
	    return format::pe::ntHeaders64(binary)->FileHeader.NumberOfSections;
    } else {
        throw RuntimeException(strenc("Unknown address type!"));
    }
}

binary_offset format::pe::sectionsStartOffset(const CPeFormat* peFormat)
{
    auto binary = peFormat->binary();
    auto addressType = peFormat->addressType();

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

pe_section_vec format::pe::readSectionList(const CPeFormat* peFormat)
{
	auto vec = pe_section_vec();

	auto numberOfSections = format::pe::numberOfSections(peFormat);
    auto offset = format::pe::sectionsStartOffset(peFormat);
    auto binary = peFormat->binary();

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

binary_offset format::pe::rvaToOffset(const CPeFormat* peFormat, const binary_offset& rva)
{
    auto sections = format::pe::readSectionList(peFormat);

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

IMAGE_DATA_DIRECTORY* format::pe::imageDataDirectory(const CPeFormat* peFormat)
{
    auto binary = peFormat->binary();
    auto addressType = peFormat->addressType();

    if (addressType == AddressType::_32_BIT) {
        return format::pe::ntHeaders32(binary)->OptionalHeader.DataDirectory;
    } else if (addressType == AddressType::_64_BIT) {
	    return format::pe::ntHeaders64(binary)->OptionalHeader.DataDirectory;
    } else {
        throw RuntimeException(strenc("Unknown address type!"));
    }
}

pe_module_map format::pe::readImportModules(const CPeFormat* peFormat)
{
    pe_module_map map { };

    auto binary = peFormat->binary();
    auto addressType = peFormat->addressType();

    auto importDataDirectory = format::pe::imageDataDirectory(peFormat)[IMAGE_DIRECTORY_ENTRY_IMPORT];
    auto currentImportDescriptorRva = importDataDirectory.VirtualAddress;
    auto currentImportDescriptorPointer = peFormat->rvaToPointer(currentImportDescriptorRva);
    auto currentImportDescriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(currentImportDescriptorPointer.ptr());

    while (currentImportDescriptor->Name != 0) {
        auto moduleName = binary->string(peFormat->rvaToOffset(currentImportDescriptor->Name));
        auto currentOriginalThunkRva = currentImportDescriptor->OriginalFirstThunk;
        auto currentThunkRva = currentImportDescriptor->FirstThunk;
        auto currentOriginalThunkPointer = peFormat->rvaToPointer(currentOriginalThunkRva);
        auto currentThunkPointer = peFormat->rvaToPointer(currentThunkRva);

        pe_import_vec moduleImports { };

        if (addressType == AddressType::_64_BIT) {
            auto currentOriginalThunk = reinterpret_cast<IMAGE_THUNK_DATA64*>(currentOriginalThunkPointer.ptr());
            auto currentThunk = reinterpret_cast<IMAGE_THUNK_DATA64*>(currentThunkPointer.ptr());

            while(currentOriginalThunk->u1.AddressOfData != 0) {
                pe_import_ptr import = nullptr;
                if (currentOriginalThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG64) {
                    import = std::make_shared<CPeImport>(
                        strenc("Ordinal"),
                        0,
                        currentOriginalThunk->u1.Ordinal & 0xFFFF,
                        currentOriginalThunkRva,
                        currentThunkRva,
                        currentOriginalThunk->u1.AddressOfData,
                        currentThunk->u1.AddressOfData,
                        sizeof(IMAGE_THUNK_DATA64)
                    );
                } else {
                    auto importByName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(peFormat->rvaToPointer(currentOriginalThunk->u1.AddressOfData).ptr());

                    import = std::make_shared<CPeImport>(
                        std::string(importByName->Name),
                        importByName->Hint,
                        0,
                        currentOriginalThunkRva,
                        currentThunkRva,
                        currentOriginalThunk->u1.AddressOfData,
                        currentThunk->u1.AddressOfData,
                        sizeof(IMAGE_THUNK_DATA64)
                    );
                }

                moduleImports.push_back(import);

                currentOriginalThunkRva += sizeof(IMAGE_THUNK_DATA64);
                currentThunkRva += sizeof(IMAGE_THUNK_DATA64);

                currentOriginalThunkPointer = peFormat->rvaToPointer(currentOriginalThunkRva);

                currentOriginalThunk++;
                currentThunk++;
            }
        } else {
            auto currentOriginalThunk = reinterpret_cast<IMAGE_THUNK_DATA32*>(currentOriginalThunkPointer.ptr());
            auto currentThunk = reinterpret_cast<IMAGE_THUNK_DATA32*>(currentThunkPointer.ptr());

            while(currentOriginalThunk->u1.AddressOfData != 0) {
                pe_import_ptr import = nullptr;
                if (currentOriginalThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG32) {
                    import = std::make_shared<CPeImport>(
                        strenc("Ordinal"),
                        0,
                        currentOriginalThunk->u1.Ordinal & 0xFFFF,
                        currentOriginalThunkRva,
                        currentThunkRva,
                        currentOriginalThunk->u1.AddressOfData,
                        currentThunk->u1.AddressOfData,
                        sizeof(IMAGE_THUNK_DATA32)
                    );
                } else {
                    auto importByName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(peFormat->rvaToPointer(currentOriginalThunk->u1.AddressOfData).ptr());

                    import = std::make_shared<CPeImport>(
                        std::string(importByName->Name),
                        importByName->Hint,
                        0,
                        currentOriginalThunkRva,
                        currentThunkRva,
                        currentOriginalThunk->u1.AddressOfData,
                        currentThunk->u1.AddressOfData,
                        sizeof(IMAGE_THUNK_DATA32)
                    );
                }

                moduleImports.push_back(import);

                currentOriginalThunkRva += sizeof(IMAGE_THUNK_DATA32);
                currentThunkRva += sizeof(IMAGE_THUNK_DATA32);

                currentOriginalThunkPointer = peFormat->rvaToPointer(currentOriginalThunkRva);

                currentOriginalThunk++;
                currentThunk++;
            }
        }

        map[moduleName] = std::make_shared<CPeModule>(
            moduleName,
            currentImportDescriptorRva,
            sizeof(IMAGE_IMPORT_DESCRIPTOR),
            moduleImports
        );

        currentImportDescriptorRva += sizeof(IMAGE_IMPORT_DESCRIPTOR);

        currentImportDescriptorPointer = peFormat->rvaToPointer(currentImportDescriptorRva);

        currentImportDescriptor++;
    }

    return map;
}

