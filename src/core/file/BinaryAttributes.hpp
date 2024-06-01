#pragma once

#include "../attributes.hpp"
#include "shared/value/Unsigned.hpp"
#include <shared/types/defines.hpp>
#include <string>

struct BinaryAttributes_t
{
    Architecture arch = Architecture::UNKNOWN;
    std::string hash = "";
    uint_8 sectionCount = 0;
    uint_8 importedModuleCount = 0;
    uint_8 importedFunctionsCount = 0;
    CUnsigned entryPoint = CUnsigned(0);
    CUnsigned sizeOfBinary = CUnsigned(0);
    CUnsigned sizeOfCode = CUnsigned(0);
};

