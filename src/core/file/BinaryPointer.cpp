#include "BinaryPointer.hpp"
#include <cstdint>

CBinaryPointer::CBinaryPointer(size_t _offsetInBinary, std::uintptr_t _loadedAtAddress)
{
	offsetInBinary = _offsetInBinary;
	loadedAtAddress = _loadedAtAddress;
}

size_t CBinaryPointer::offset()
{
	return offsetInBinary;
}

std::uintptr_t CBinaryPointer::ptr()
{
	return loadedAtAddress;
}

