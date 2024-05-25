#include "PeImport.hpp"
#include "core/file/format/pe/defines.hpp"
#include <shared/value/AddressType.hpp>
#include "functions.hpp"
#include <memory>
#include <shared/self_obfuscation/strenc.hpp>

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
    auto importDescriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(importDescriptorPtr.ptr());

    while (importDescriptor->Name != 0) {
        auto dllName = binary->string(importDescriptor->Name);

        if (addressType == AddressType::_64_BIT) {
            auto originalFirstThunk = reinterpret_cast<IMAGE_THUNK_DATA64*>(binary->pointer(importDescriptor->First.OriginalFirstThunk).ptr());
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
            auto originalFirstThunk = reinterpret_cast<IMAGE_THUNK_DATA32*>(binary->pointer(importDescriptor->First.OriginalFirstThunk).ptr());
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

    return vec;
}

