#ifndef CORE_SHARED__BINARY_POINTER_HPP_
#define CORE_SHARED__BINARY_POINTER_HPP_

#include <shared/types/defines.hpp>

class CBinaryPointer
{
    binary_offset _offsetInBinary;
    uint_auto _loadedAtAddress;
public:
    CBinaryPointer(binary_offset offsetInBinary, uint_auto loadedAtAddress);
    binary_offset offset() const;
    uint_auto ptr() const;
    CBinaryPointer shift(int _offset) const;
};

#endif // CORE_SHARED__BINARY_POINTER_HPP_
