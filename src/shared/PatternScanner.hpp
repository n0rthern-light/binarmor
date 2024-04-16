#ifndef PATTERN_SCAN_H
#define PATTERN_SCAN_H

#include "DynamicLinker.hpp"

class CPatternScanner
{
    CDynamicLinker* linker;
public:
    CPatternScanner(CDynamicLinker* linker): linker(linker) {};
    DWORD FindPatternAddress(const char* module, const char* pattern);
};

#endif