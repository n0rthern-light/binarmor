#ifndef PATTERN_SCAN_H
#define PATTERN_SCAN_H

#include <Windows.h>

DWORD FindPattern(const char* module, const char* pattern_string, const char* mask);
DWORD FindPatternIDA(const char * szModule, const char * szSignature);

#endif