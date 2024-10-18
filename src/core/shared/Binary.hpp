#ifndef CORE_SHARED__BINARY_HPP_
#define CORE_SHARED__BINARY_HPP_

#include <shared/types/defines.hpp>
#include <string>
#include "BinaryPointer.hpp"
#include <shared/crypto/IHasher.hpp>

namespace program::core::shared {
    class CBinary
    {
        const program::shared::types::byte_vec m_bytes;
        program::shared::types::byte_ptr at(const program::shared::types::binary_offset& offset) const;
    public:
        CBinary(const program::shared::types::byte_vec& bytes);
        CBinary part(const program::shared::types::binary_offset& offset = 0, const program::shared::types::binary_offset& count = 0) const;
        program::shared::types::byte_vec bytes() const;
        std::string string(const program::shared::types::binary_offset& offset = 0) const;
        program::shared::types::binary_offset size() const;
        CBinaryPointer pointer(const program::shared::types::binary_offset& offset) const;
        bool offsetExists(const program::shared::types::binary_offset& offset) const;
        std::string hash(const program::shared::crypto::IHasher* hasher) const;
        bool allBytesAre(unsigned char byte) const;

        bool operator==(const CBinary& other) const;
    };
}

#endif // CORE_SHARED__BINARY_HPP_
