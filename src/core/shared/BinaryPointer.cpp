#include "BinaryPointer.hpp"

using namespace program::core::shared;
using namespace program::shared::types;

CBinaryPointer::CBinaryPointer(binary_offset offsetInBinary, uint_auto loadedAtAddress)
{
    m_offsetInBinary = offsetInBinary;
    m_loadedAtAddress = loadedAtAddress;
}

binary_offset CBinaryPointer::offset() const
{
    return m_offsetInBinary;
}

uint_auto CBinaryPointer::ptr() const
{
    return m_loadedAtAddress;
}

CBinaryPointer CBinaryPointer::shift(int _offset) const
{
    return CBinaryPointer(offset() + _offset, ptr() + _offset);
}

bool CBinaryPointer::isNullptr() const
{
    return m_loadedAtAddress == 0;
}
