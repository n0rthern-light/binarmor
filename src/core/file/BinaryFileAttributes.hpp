#ifndef CORE_FILE__BINARY_ATTRIBUTES_HPP_
#define CORE_FILE__BINARY_ATTRIBUTES_HPP_

#include "../shared/attributes.hpp"
#include "shared/value/Unsigned.hpp"
#include <shared/types/defines.hpp>
#include <string>

namespace program::core::file {
    struct BinaryFileAttributes_t
    {
        program::core::shared::Format format = program::core::shared::Format::UNKNOWN;
        program::core::shared::Architecture arch = program::core::shared::Architecture::UNKNOWN;
        program::core::shared::Type type = program::core::shared::Type::UNKNOWN;
        std::string hash = "";
        uint_8 sectionCount = 0;
        uint_8 importedModuleCount = 0;
        uint_8 importedFunctionsCount = 0;
        CUnsigned entryPoint = CUnsigned(0);
        CUnsigned sizeOfBinary = CUnsigned(0);
        CUnsigned sizeOfCode = CUnsigned(0);
        bool isProtected = false;
    };
}

#endif // CORE_FILE__BINARY_ATTRIBUTES_HPP_
