#include "BinaryPointer.hpp"
#include <cstdint>

CBinaryPointer::CBinaryPointer(size_t offsetInBinary, std::uintptr_t loadedAtAddress)
{
	_offsetInBinary = offsetInBinary;
	_loadedAtAddress = loadedAtAddress;
}

size_t CBinaryPointer::offset()
{
	return _offsetInBinary;
}

std::uintptr_t CBinaryPointer::ptr()
{
	return _loadedAtAddress;
}

CBinaryPointer CBinaryPointer::shift(int _offset)
{
    return CBinaryPointer(offset() + _offset, ptr() + _offset);
}

