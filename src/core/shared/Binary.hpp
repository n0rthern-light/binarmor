#ifndef CORE_SHARED__BINARY_HPP_
#define CORE_SHARED__BINARY_HPP_

#include <shared/types/defines.hpp>
#include <string>
#include "BinaryPointer.hpp"
#include <shared/crypto/IHasher.hpp>

class CBinary
{
    const byte_vec _bytes;
    byte_ptr at(const binary_offset& offset) const;
public:
    CBinary(const byte_vec& bytes);
    CBinary part(const binary_offset& offset = 0, const binary_offset& count = 0) const;
    byte_vec bytes() const;
    std::string string(const binary_offset& offset = 0) const;
    binary_offset size() const;
    CBinaryPointer pointer(const binary_offset& offset) const;
    bool offsetExists(const binary_offset& offset) const;
    std::string hash(const IHasher* hasher) const;

    bool operator==(const CBinary& other) const;
};

#endif // CORE_SHARED__BINARY_HPP_
