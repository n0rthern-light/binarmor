#include "PeImport.hpp"
#include "core/file/format/pe/defines.hpp"
#include "shared/value/AddressType.hpp"
#include "functions.hpp"

CPeImport::CPeImport(
    const std::string& module,
    const std::string& name,
    const uint_16& hint,
    const uint_32& ordinal
) {
    _module = module;
    _name = name;
    _hint = hint;
    _ordinal = ordinal;
}

pe_import_vec CPeImport::readList(CBinary *binary, AddressType addressType)
{
    pe_import_vec vec{ };
    auto dataDirectory = format::pe::imageDataDirectoryEntry(binary, addressType, IMAGE_DIRECTORY_ENTRY_IMPORT);

    if (dataDirectory->VirtualAddress == 0) {
        return vec;
    }

    auto importDescriptorPtr = binary->pointer(dataDirectory->VirtualAddress);
    IMAGE_IMPORT_DESCRIPTOR* importDescriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(importDescriptorPtr.ptr());

    while (importDescriptor->Name != 0) {
        //const char* dllName = reinterpret_cast<const char*>(binary->pointer(importDescriptor->Name).ptr());
        auto dllName = binary->string(importDescriptor->Name);
        // parse imports...
    }

    return vec;
}

