#ifndef CORE_FILE__BINARY_ATTRIBUTES_HPP_
#define CORE_FILE__BINARY_ATTRIBUTES_HPP_

#include "../shared/attributes.hpp"
#include "shared/value/Unsigned.hpp"
#include <shared/types/defines.hpp>
#include <string>

struct BinaryFileAttributes_t
{
    Format format = Format::UNKNOWN;
    Architecture arch = Architecture::UNKNOWN;
    Type type = Type::UNKNOWN;
    std::string hash = "";
    uint_8 sectionCount = 0;
    uint_8 importedModuleCount = 0;
    uint_8 importedFunctionsCount = 0;
    CUnsigned entryPoint = CUnsigned(0);
    CUnsigned sizeOfBinary = CUnsigned(0);
    CUnsigned sizeOfCode = CUnsigned(0);
    bool isProtected = false;
};

#endif // CORE_FILE__BINARY_ATTRIBUTES_HPP_
