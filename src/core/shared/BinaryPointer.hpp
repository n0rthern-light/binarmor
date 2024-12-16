#ifndef CORE_SHARED__BINARY_POINTER_HPP_
#define CORE_SHARED__BINARY_POINTER_HPP_

#include <shared/types/defines.hpp>

namespace program::core::shared {
    class CBinaryPointer
    {
        program::shared::types::binary_offset m_offsetInBinary;
        program::shared::types::uint_auto m_loadedAtAddress;
    public:
        CBinaryPointer(program::shared::types::binary_offset offsetInBinary, program::shared::types::uint_auto loadedAtAddress);
        program::shared::types::binary_offset offset() const;
        program::shared::types::uint_auto ptr() const;
        CBinaryPointer shift(int _offset) const;
        bool isNullptr() const;
    };
}

#endif // CORE_SHARED__BINARY_POINTER_HPP_
