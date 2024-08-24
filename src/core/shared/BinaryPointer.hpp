#ifndef CORE_SHARED__BINARY_POINTER_HPP_
#define CORE_SHARED__BINARY_POINTER_HPP_

#include <shared/types/defines.hpp>

class CBinaryPointer
{
    binary_offset m_offsetInBinary;
    uint_auto m_loadedAtAddress;
public:
    CBinaryPointer(binary_offset offsetInBinary, uint_auto loadedAtAddress);
    binary_offset offset() const;
    uint_auto ptr() const;
    CBinaryPointer shift(int _offset) const;
    bool isNullptr() const;
};

#endif // CORE_SHARED__BINARY_POINTER_HPP_
