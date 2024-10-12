#include "functions.hpp"
#include "core/format/pe/PeSection.hpp"
#include "core/shared/Binary.hpp"
#include "core/shared/SectionPermissions.hpp"
#include "defines.hpp"
#include "shared/value/AddressType.hpp"
#include "shared/value/ByteVecOperations.hpp"
#include <format>
#include <shared/self_obfuscation/strenc.hpp>
#include <shared/RuntimeException.hpp>
#include <stdio.h>
#include <string>

IMAGE_DOS_HEADER* format::pe::dosHeader(const CBinary& binary)
{
    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(binary.pointer(0).ptr());

    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        throw RuntimeException(strenc("Invalid IMAGE_DOS_SIGNATURE"));
    }

    return dosHeader;
}

template <typename NT_HEADERS>
NT_HEADERS* format::pe::ntHeaders(const CBinary& binary)
{
    auto dosHeader = format::pe::dosHeader(binary);

    auto ntHeaders = reinterpret_cast<NT_HEADERS*>(binary.pointer(dosHeader->e_lfanew).ptr());

    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
        throw RuntimeException(strenc("Invalid IMAGE_NT_SIGNATURE"));
    }

    return ntHeaders;
}

IMAGE_NT_HEADERS32* format::pe::ntHeaders32(const CBinary& binary)
{
    return format::pe::ntHeaders<IMAGE_NT_HEADERS32>(binary);
}

IMAGE_NT_HEADERS64* format::pe::ntHeaders64(const CBinary& binary)
{
    return format::pe::ntHeaders<IMAGE_NT_HEADERS64>(binary);
}


uint_16 format::pe::numberOfSections(const CPeFormat& peFormat)
{
    auto binary = peFormat.binary();
    auto addressType = peFormat.addressType();

    if (addressType == AddressType::_32_BIT) {
        return format::pe::ntHeaders32(binary)->FileHeader.NumberOfSections;
    } else if (addressType == AddressType::_64_BIT) {
        return format::pe::ntHeaders64(binary)->FileHeader.NumberOfSections;
    } else {
        throw RuntimeException(strenc("Unknown address type!"));
    }
}

binary_offset format::pe::sectionsStartOffset(const CPeFormat& peFormat)
{
    auto binary = peFormat.binary();
    auto addressType = peFormat.addressType();

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

pe_section_vec format::pe::readSectionList(const CPeFormat& peFormat)
{
    auto vec = pe_section_vec();

    auto numberOfSections = format::pe::numberOfSections(peFormat);
    auto offset = format::pe::sectionsStartOffset(peFormat);
    auto binary = peFormat.binary();

    auto binaryPointer = binary.pointer(offset);
    for(int i = 0; i < numberOfSections; ++i)
    {
        auto sectionOrigin = binaryPointer.shift(i * sizeof(IMAGE_SECTION_HEADER));
        auto sectionHeader = *reinterpret_cast<IMAGE_SECTION_HEADER*>(sectionOrigin.ptr());
        auto section = std::make_shared<CPeSection>(sectionOrigin.offset(), sectionHeader);
        vec.push_back(section);
    }

    return vec;
}

binary_offset format::pe::rvaToOffset(const CPeFormat& peFormat, const binary_offset rva)
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

    throw RuntimeException(std::format(strenc("Could not convert RVA: 0x{:x} to Raw Offset"), rva));
}

IMAGE_DATA_DIRECTORY* format::pe::imageDataDirectory(const CPeFormat& peFormat)
{
    auto binary = peFormat.binary();
    auto addressType = peFormat.addressType();

    if (addressType == AddressType::_32_BIT) {
        return format::pe::ntHeaders32(binary)->OptionalHeader.DataDirectory;
    } else if (addressType == AddressType::_64_BIT) {
        return format::pe::ntHeaders64(binary)->OptionalHeader.DataDirectory;
    } else {
        throw RuntimeException(strenc("Unknown address type!"));
    }
}

template <typename IMAGE_THUNK_DATA, typename IMAGE_ORDINAL_FLAG>
pe_import_vec format::pe::readModuleImports(const CPeFormat& peFormat, const IMAGE_IMPORT_DESCRIPTOR* imageImportDescriptor, const IMAGE_ORDINAL_FLAG& imageOrdinalFlag)
{
    pe_import_vec moduleImports { };

    auto currentOriginalThunkRva = imageImportDescriptor->OriginalFirstThunk;
    auto currentThunkRva = imageImportDescriptor->FirstThunk;
    auto currentOriginalThunkPointer = peFormat.rvaToPointer(currentOriginalThunkRva);
    auto currentThunkPointer = peFormat.rvaToPointer(currentThunkRva);

    auto currentOriginalThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(currentOriginalThunkPointer.ptr());
    auto currentThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(currentThunkPointer.ptr());

    while(currentOriginalThunk->u1.AddressOfData != 0) {
        pe_import_ptr import = nullptr;
        if (currentOriginalThunk->u1.Ordinal & imageOrdinalFlag) {
            import = std::make_shared<CPeImport>(
                strenc("Ordinal"),
                0,
                currentOriginalThunk->u1.Ordinal & 0xFFFF,
                currentOriginalThunkRva,
                currentThunkRva,
                currentOriginalThunkRva, // no pointer to import by name, so just ref to self; might be nullptr either
                currentThunkRva,
                sizeof(IMAGE_THUNK_DATA)
            );
        } else {
            auto importByName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(peFormat.rvaToPointer(currentOriginalThunk->u1.AddressOfData).ptr());

            import = std::make_shared<CPeImport>(
                std::string(importByName->Name),
                importByName->Hint,
                0,
                currentOriginalThunkRva,
                currentThunkRva,
                currentOriginalThunk->u1.AddressOfData, // import by name address ptr
                currentThunk->u1.AddressOfData,
                sizeof(IMAGE_THUNK_DATA)
            );
        }

        moduleImports.push_back(import);

        currentOriginalThunkRva += sizeof(IMAGE_THUNK_DATA);
        currentThunkRva += sizeof(IMAGE_THUNK_DATA);

        currentOriginalThunkPointer = peFormat.rvaToPointer(currentOriginalThunkRva);

        currentOriginalThunk++;
        currentThunk++;
    }

    return moduleImports;
}

pe_module_map format::pe::readImportModules(const CPeFormat& peFormat)
{
    pe_module_map map { };

    auto binary = peFormat.binary();
    auto addressType = peFormat.addressType();

    auto importDataDirectory = format::pe::imageDataDirectory(peFormat)[IMAGE_DIRECTORY_ENTRY_IMPORT];
    auto currentImportDescriptorRva = importDataDirectory.VirtualAddress;
    auto currentImportDescriptorPointer = peFormat.rvaToPointer(currentImportDescriptorRva);
    auto currentImportDescriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(currentImportDescriptorPointer.ptr());

    while (currentImportDescriptor->Name != 0) {
        auto moduleName = binary.string(peFormat.rvaToOffset(currentImportDescriptor->Name));
        pe_import_vec moduleImports = { };

        if (addressType == AddressType::_64_BIT) {
            moduleImports = format::pe::readModuleImports<IMAGE_THUNK_DATA64, uint_64>(peFormat, currentImportDescriptor, IMAGE_ORDINAL_FLAG64);
        } else {
            moduleImports = format::pe::readModuleImports<IMAGE_THUNK_DATA32, uint_32>(peFormat, currentImportDescriptor, IMAGE_ORDINAL_FLAG32);
        }

        map[moduleName] = std::make_shared<CPeModule>(
            moduleName,
            currentImportDescriptorRva,
            sizeof(IMAGE_IMPORT_DESCRIPTOR),
            moduleImports
        );

        currentImportDescriptorRva += sizeof(IMAGE_IMPORT_DESCRIPTOR);
        currentImportDescriptorPointer = peFormat.rvaToPointer(currentImportDescriptorRva);
        currentImportDescriptor++;
    }

    return map;
}

uint_32 format::pe::convertSectionPermissionsToCharacteristics(const CSectionPermissions& permissions)
{
    uint_32 characteristics = IMAGE_SCN_MEM_READ;

    if (
        permissions.hasPermissionTo(SectionPermissionType::READ) &&
        !permissions.hasPermissionTo(SectionPermissionType::WRITE) &&
        !permissions.hasPermissionTo(SectionPermissionType::EXECUTE)
    ) {
        characteristics |= IMAGE_SCN_CNT_INITIALIZED_DATA;
    }

    if (permissions.hasPermissionTo(SectionPermissionType::WRITE)) {
        characteristics |= IMAGE_SCN_MEM_WRITE;
    }

    if (permissions.hasPermissionTo(SectionPermissionType::EXECUTE)) {
        characteristics |= IMAGE_SCN_MEM_EXECUTE;
        characteristics |= IMAGE_SCN_CNT_CODE;
    }

    return characteristics;
}

CSectionPermissions format::pe::convertCharacteristicsToSectionPermissions(const uint_32 characteristics)
{
    auto permissions = CSectionPermissions { };
    auto checkProperty = [=](uint_32 property) -> bool { return (characteristics & property) == property; };

    if (checkProperty(IMAGE_SCN_MEM_READ)) {
        permissions = permissions.withPermission(SectionPermissionType::READ);
    }

    if (checkProperty(IMAGE_SCN_MEM_WRITE)) {
        permissions = permissions.withPermission(SectionPermissionType::WRITE);
    }

    if (checkProperty(IMAGE_SCN_MEM_EXECUTE)) {
        permissions = permissions.withPermission(SectionPermissionType::EXECUTE);
    }

    return permissions;
}

IMAGE_SECTION_HEADER format::pe::createNextSectionHeader(
    const uint_32 fileAlignment,
    const uint_32 sectionAlignment,
    const IMAGE_SECTION_HEADER& previousSectionHeader,
    const std::string& name,
    binary_offset size,
    const CSectionPermissions permissions
) {
    IMAGE_SECTION_HEADER newSectionHeader = {};
    strncpy(reinterpret_cast<char*>(newSectionHeader.Name), name.c_str(), IMAGE_SIZEOF_SHORT_NAME);

    newSectionHeader.VirtualAddress = (previousSectionHeader.VirtualAddress + previousSectionHeader.Misc.VirtualSize + sectionAlignment - 1) & ~(sectionAlignment - 1);
    newSectionHeader.SizeOfRawData = (size + fileAlignment - 1) & ~(fileAlignment - 1);
    newSectionHeader.PointerToRawData = (previousSectionHeader.PointerToRawData + previousSectionHeader.SizeOfRawData + fileAlignment - 1) & ~(fileAlignment - 1);
    newSectionHeader.Misc.VirtualSize = size; // this might be adjusted to match raw data size i think
    newSectionHeader.Characteristics = format::pe::convertSectionPermissionsToCharacteristics(permissions);

    return newSectionHeader;
}

CPeFormat format::pe::addSection(
        const CPeFormat& peFormat,
        const std::string& name,
        binary_offset size,
        const CSectionPermissions permissions
) {
    const auto binary = peFormat.binary();
    const auto addressType = peFormat.addressType();

    IMAGE_DOS_HEADER* dosHeader = format::pe::dosHeader(binary);
    binary_offset sectionAlignment, fileAlignment;

    if (addressType == AddressType::_32_BIT) {
        const auto ntHeaders = format::pe::ntHeaders32(binary);
        sectionAlignment = ntHeaders->OptionalHeader.SectionAlignment;
        fileAlignment = ntHeaders->OptionalHeader.FileAlignment;
    } else if (addressType == AddressType::_64_BIT) {
        const auto ntHeaders = format::pe::ntHeaders64(binary);
        sectionAlignment = ntHeaders->OptionalHeader.SectionAlignment;
        fileAlignment = ntHeaders->OptionalHeader.FileAlignment;
    } else {
        throw RuntimeException("Unknown address type!");
    }

    const auto numberOfSections = format::pe::numberOfSections(peFormat);
    const auto offset = format::pe::sectionsStartOffset(peFormat);
    const auto& sections = peFormat.peSections();
    const auto& firstSection = sections.front();
    const auto& lastSection = sections.back();
    const auto lastSectionHeaderOffset = lastSection->headerOffset();
    const auto lastSectionHeader = *reinterpret_cast<IMAGE_SECTION_HEADER*>(binary.pointer(lastSectionHeaderOffset).ptr());
    const auto sizeOfHeaders = sizeof(IMAGE_SECTION_HEADER);
    const auto newSectionHeaderOffset = lastSectionHeaderOffset + sizeOfHeaders;

    // check if there is still a place for new section, if not realignment must be done, which is... NOT READY
    const auto spaceLeftInHeaders = firstSection->baseAddress().get() - newSectionHeaderOffset;
    if (spaceLeftInHeaders < sizeOfHeaders) {
        throw RuntimeException(strenc("No more space left for a new section header"));
    }
    const auto newSectionHeaderCurrentBytes = binary.part(newSectionHeaderOffset, spaceLeftInHeaders);
    if (newSectionHeaderCurrentBytes.allBytesAre(PE_SECTION_NULL_BYTE) == false) {
        throw RuntimeException(strenc("Section header seem to be already initialized"));
    }

    const auto newSectionHeader = format::pe::createNextSectionHeader(fileAlignment, sectionAlignment, lastSectionHeader, name, size, permissions);
    auto newSectionHeaderBytes = byte_vec(sizeOfHeaders , PE_SECTION_NULL_BYTE);
    std::memcpy(&newSectionHeaderBytes[0], &newSectionHeader, sizeOfHeaders);

    auto bytes = binary.bytes();
    bytes = CByteVecOperations::bytesModify(bytes, newSectionHeaderOffset, newSectionHeaderBytes);
    bytes = CByteVecOperations::bytesInsert(bytes, newSectionHeader.PointerToRawData, byte_vec(newSectionHeader.SizeOfRawData, PE_SECTION_NULL_BYTE));

    auto newBinary = CBinary { bytes };

    if (addressType == AddressType::_32_BIT) {
        auto ntHeaders = format::pe::ntHeaders32(newBinary);
        ntHeaders->FileHeader.NumberOfSections++;
        ntHeaders->OptionalHeader.SizeOfImage = newSectionHeader.VirtualAddress + newSectionHeader.Misc.VirtualSize;
    } else if (addressType == AddressType::_64_BIT) {
        auto ntHeaders = format::pe::ntHeaders64(newBinary);
        ntHeaders->FileHeader.NumberOfSections++;
        ntHeaders->OptionalHeader.SizeOfImage = newSectionHeader.VirtualAddress + newSectionHeader.Misc.VirtualSize;
    }

    return CPeFormat{ newBinary };
}
