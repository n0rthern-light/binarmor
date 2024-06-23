#pragma once

#include "shared/value/Uuid.hpp"
#include <map>
#include <shared/types/defines.hpp>
#include <vector>

enum class BinaryModificationType
{
    APPEND_SECTION = 0,
    APPEND_DATA = 1,
    APPEND_CODE = 2,
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
    const byte_vec bytes;

    static BinaryModificationDiff_t add(binary_offset offset, const byte_vec& bytes);
    static BinaryModificationDiff_t remove(binary_offset offset, binary_offset size);
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
    bool operator ==(const CBinaryModification& other) const;
};

