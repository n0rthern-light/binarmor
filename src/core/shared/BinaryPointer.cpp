#include "BinaryPointer.hpp"

CBinaryPointer::CBinaryPointer(binary_offset offsetInBinary, uint_auto loadedAtAddress)
{
    _offsetInBinary = offsetInBinary;
    _loadedAtAddress = loadedAtAddress;
}

binary_offset CBinaryPointer::offset()
{
    return _offsetInBinary;
}

uint_auto CBinaryPointer::ptr()
{
    return _loadedAtAddress;
}

CBinaryPointer CBinaryPointer::shift(int _offset)
{
    return CBinaryPointer(offset() + _offset, ptr() + _offset);
}

