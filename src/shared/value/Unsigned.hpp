#ifndef SHARED_VALUE__UNSIGNED_HPP_
#define SHARED_VALUE__UNSIGNED_HPP_

#include "AddressType.hpp"
#include "../types/defines.hpp"
#include <string>

class CUnsigned
{
    union {
        uint_32 _32;
        uint_64 _64;
    } address;
    AddressType type;

public:
    CUnsigned(int _address);
    CUnsigned(uint_32 _address);
    CUnsigned(uint_64 _address);
    AddressType bitType() const;
    uint_32 get32() const;
    uint_64 get64() const;
    uint_auto get() const;
    std::string asDecimalString() const;
    std::string asShortHexString() const;
    std::string asFullHexString() const;
    byte_vec asLittleEndianBytes(unsigned int byteCount) const;
    bool operator==(const CUnsigned& other) const;
    bool operator!=(const CUnsigned& other) const;
};

#endif // SHARED_VALUE__UNSIGNED_HPP_
