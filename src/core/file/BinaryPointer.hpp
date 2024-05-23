#pragma once

#include <cstdint>
#include <cstddef>

class CBinaryPointer
{
	size_t _offsetInBinary;
	std::uintptr_t _loadedAtAddress;
public:
	CBinaryPointer(size_t offsetInBinary, std::uintptr_t loadedAtAddress);
	size_t offset();
	std::uintptr_t ptr();
    CBinaryPointer shift(int _offset);
};

