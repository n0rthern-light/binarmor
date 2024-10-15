#ifndef CORE_FILE__BINARY_MODIFICATION_HPP_
#define CORE_FILE__BINARY_MODIFICATION_HPP_

#include "shared/value/Uuid.hpp"
#include <shared/types/defines.hpp>

namespace program::core::file {
    enum class BinaryModificationType
    {
        ADD_SECTION = 0,
        WRITE_DATA = 1,
        WRITE_CODE = 2,
        WRITE_IMPORT = 3,
        INIT_STARTUP_CODE = 4,
        ENCRYPT_OLD_IMPORT = 5,
        RENAME_SECTION = 6,
        ENCRYPT_DATA = 7
    };

    enum class BinaryModificationDiffType
    {
        ADD = 0,
        REMOVE = 1,
    };

    struct BinaryModificationDiff_t
    {
        const CUuid id;
        const BinaryModificationDiffType type;
        const binary_offset offset;
        const binary_offset size;
        const byte_vec oldBytes;
        const byte_vec newBytes;

        static BinaryModificationDiff_t add(binary_offset offset, const byte_vec& newBytes);
        static BinaryModificationDiff_t remove(binary_offset offset, const byte_vec& oldBytes);
    };

    using vec_diff = std::vector<const BinaryModificationDiff_t>;

    class CBinaryModification
    {
        const CUuid m_id;
        const BinaryModificationType m_type;
        const vec_diff m_vecDiff;
        const std::vector<CUuid> m_requiredModificationIds;
    public:
        CBinaryModification(
            const CUuid& id,
            BinaryModificationType type,
            const vec_diff& vecDiff,
            const std::vector<CUuid>& requiredModificationIds
        );
        CUuid id() const;
        BinaryModificationType type() const;
        std::vector<CUuid> requiredModificationIds() const;
        const byte_vec apply(byte_vec targetBytes) const;
        const binary_offset firstByteAddress() const;
        const binary_offset firstByteAddressOfType(BinaryModificationDiffType type) const;
        const binary_offset firstAddByteAddress() const;
        int totalSizeDiff() const;
        bool operator ==(const CBinaryModification& other) const;
    };
}

#endif // CORE_FILE__BINARY_MODIFICATION_HPP_
