#include "PatternScanner.hpp"
#include "strenc.hpp"
#include "win_api.hpp"
#ifdef DEBUG
#include <iostream>
#endif

#define INRANGE(x, a, b) (x >= a && x <= b)
#define getBits(x) (INRANGE((x & (~0x20)), strenc('A'), strenc('F')) ? ((x & (~0x20)) - strenc('A') + 0xa) : (INRANGE(x, strenc('0'), strenc('9')) ? x - strenc('0') : 0))
#define getByte(x) (getBits(x[0]) << 4 | getBits(x[1]))

DWORD CPatternScanner::FindPatternAddress(const char* module, const char* pattern)
{
    MODULEINFO modInfo;
    this->linker->GetFunction(KERNEL32, KERNEL32_GetModuleInformation)->call<pGetModuleInformation>(
        this->linker->GetFunction(KERNEL32, KERNEL32_GetCurrentProcess)->call<pGetCurrentProcess>(),
        this->linker->GetFunction(KERNEL32, KERNEL32_GetModuleHandleA)->call<pGetModuleHandleA>(module),
        &modInfo,
        sizeof(MODULEINFO)
    );

    DWORD startAddress = (DWORD)modInfo.lpBaseOfDll;
	DWORD endAddress = startAddress + modInfo.SizeOfImage;

#ifdef DEBUG
std::cout << "startAddress: " << std::hex << startAddress << " endAddress: " << std::hex << endAddress << std::endl;
#endif

	const char* pat = pattern;
	DWORD firstMatch = 0;
	for (DWORD pCur = startAddress; pCur < endAddress; pCur++) {
		if (!*pat)
			return firstMatch;
		if (*(PBYTE)pat == strenc('\?') || *(BYTE*)pCur == getByte(pat)) {
			if (!firstMatch)
				firstMatch = pCur;
			if (!pat[2])
				return firstMatch;
			if (*(PWORD)pat == strenc('\?\?') || *(PBYTE)pat != strenc('\?'))
				pat += 3;
			else
				pat += 2;
		}
		else {
			pat = pattern;
			firstMatch = 0;
		}
	}

	return 0;
}
