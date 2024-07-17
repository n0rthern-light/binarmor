#include "BinaryPointer.hpp"

CBinaryPointer::CBinaryPointer(binary_offset offsetInBinary, uint_auto loadedAtAddress)
{
    _offsetInBinary = offsetInBinary;
    _loadedAtAddress = loadedAtAddress;
}

binary_offset CBinaryPointer::offset() const
{
    return _offsetInBinary;
}

uint_auto CBinaryPointer::ptr() const
{
    return _loadedAtAddress;
}

CBinaryPointer CBinaryPointer::shift(int _offset) const
{
    return CBinaryPointer(offset() + _offset, ptr() + _offset);
}

