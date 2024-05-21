#pragma once

#include <cstdint>
#include <cstddef>

class CBinaryPointer
{
	size_t offsetInBinary;
	std::uintptr_t loadedAtAddress;
public:
	CBinaryPointer(size_t _offsetInBinary, std::uintptr_t _loadedAtAddress);
	size_t offset();
	std::uintptr_t ptr();
};

