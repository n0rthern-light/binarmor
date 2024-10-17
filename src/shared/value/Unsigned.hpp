#ifndef SHARED_VALUE__UNSIGNED_HPP_
#define SHARED_VALUE__UNSIGNED_HPP_

#include "AddressType.hpp"
#include "../types/defines.hpp"
#include <string>

namespace program::shared::value
{
    class CUnsigned
    {
        union {
        types::uint_32 m_32;
        types::uint_64 m_64;
        } m_address;
        AddressType m_type;

    public:
        CUnsigned(int address);
        CUnsigned(types::uint_32 address);
        CUnsigned(types::uint_64 address);
        AddressType bitType() const;
        types::uint_32 get32() const;
        types::uint_64 get64() const;
        types::uint_auto get() const;
        std::string asDecimalString() const;
        std::string asShortHexString() const;
        std::string asFullHexString() const;
        types::byte_vec asLittleEndianBytes(unsigned int byteCount) const;
        bool operator==(const CUnsigned& other) const;
        bool operator!=(const CUnsigned& other) const;
    };
}

#endif // SHARED_VALUE__UNSIGNED_HPP_
