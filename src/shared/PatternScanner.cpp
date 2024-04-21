#include "PatternScanner.hpp"
#include "RuntimeException.hpp"
#include "strenc.hpp"
#include "win_api.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#ifdef _DEBUG
#include <iostream>
#endif

inline bool isValidHex(const std::string& str) {
    if (str.length() != 2) {
        return false;
    }

    for (char c : str) {
        if (!std::isxdigit(c)) {
            return false;
        }
    }

    return true;
}

inline bool isValidPattern(const std::string& str) {
    if (str == strenc("??") || str == strenc("?")) {
        return true;
    }

    return isValidHex(str);
}

uintptr_t CPatternScanner::FindPatternAddress(const char* module, const char* pattern)
{
    MODULEINFO modInfo;
    auto moduleHandle = this->linker->GetFunction(KERNEL32, KERNEL32_GetModuleHandleA)->call<pGetModuleHandleA>(module);
    this->linker->GetFunction(KERNEL32, KERNEL32_GetModuleInformation)->call<pGetModuleInformation>(
        this->linker->GetFunction(KERNEL32, KERNEL32_GetCurrentProcess)->call<pGetCurrentProcess>(),
        moduleHandle,
        &modInfo,
        sizeof(MODULEINFO)
    );

    auto startAddress = reinterpret_cast<uintptr_t>(moduleHandle);
	auto endAddress = startAddress + modInfo.SizeOfImage;

#ifdef _DEBUG
std::cout << "startAddress: " << std::hex << startAddress << " endAddress: " << std::hex << endAddress << std::endl;
#endif

    std::string strPattern = std::string(pattern);
    unsigned short patternByteCount = std::count(strPattern.begin(), strPattern.end(), ' ') + 1;
    std::string token;

    if (strPattern.back() != ' ') {
        strPattern += ' ';
    }

    for(auto currentAddress = startAddress; currentAddress < endAddress - patternByteCount; currentAddress++)
    {
        unsigned short correctBytes = 0;

        size_t start = 0, end;
        while ((end = strPattern.find(' ', start)) != std::string::npos) {
            token = strPattern.substr(start, end - start);

            if (token.empty()) {
                throw RuntimeException("Found empty token in pattern!");
            }

            if (!isValidPattern(token)) {
                throw RuntimeException("Found invalid token in pattern: " + strPattern);
            }

            if (token == strenc("??") || token == strenc("?")) {
                correctBytes++;
            } else {
                unsigned char tokenByte = static_cast<unsigned char>(std::stoi(token, 0, 16));
                unsigned char memoryByte = *reinterpret_cast<unsigned char*>(currentAddress + correctBytes);

                if (tokenByte != memoryByte) {
                    break;
                }

                correctBytes++;
            }

            start = end + 1;
        }

        if (correctBytes == patternByteCount) {
            return currentAddress;
        }
    }

	return 0;
}
