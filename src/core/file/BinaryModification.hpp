#pragma once

#include "core/Binary.hpp"
#include "shared/value/Uuid.hpp"
#include <shared/types/defines.hpp>
#include <vector>

enum class BinaryModificationType
{
    APPEND_SECTION = 0,
    APPEND_DATA = 1,
    APPEND_CODE = 2,
};

class CBinaryModification
{
    const CUuid m_id;
    const BinaryModificationType m_type;
    const binary_offset m_offset;
    const byte_vec m_bytes;
    const std::vector<CUuid> m_requiredModificationIds;
public:
    CBinaryModification(
        const CUuid& id,
        BinaryModificationType type,
        binary_offset offset,
        const byte_vec& bytes,
        const std::vector<CUuid>& requiredModificationIds
    ):  m_id(id),
        m_type(type),
        m_offset(offset),
        m_bytes(bytes),
        m_requiredModificationIds(requiredModificationIds)
    { }
    CUuid id() const { return m_id; }
    BinaryModificationType type() const { return m_type; }
    binary_offset offset() const { return m_offset; }
    const byte_vec bytes() const { return m_bytes; }
    binary_offset size() const { return m_bytes.size(); }
    std::vector<CUuid> requiredModificationIds() const { return m_requiredModificationIds; }
    bool operator ==(const CBinaryModification& other) const { return id() == other.id(); };
};

