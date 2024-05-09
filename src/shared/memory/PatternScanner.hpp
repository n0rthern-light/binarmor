#pragma once

#include "../self_obfuscation/DynamicLinker.hpp"

class CPatternScanner
{
    CDynamicLinker* linker;
public:
    CPatternScanner(CDynamicLinker* linker): linker(linker) {};
    uintptr_t FindPatternAddress(const char* module, const char* pattern);
};
