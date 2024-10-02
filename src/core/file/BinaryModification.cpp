#include "BinaryModification.hpp"
#include "core/modification/ModificationException.hpp"
#include "shared/RuntimeException.hpp"
#include "shared/diff/diff_match_patch.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include "shared/types/defines.hpp"
#include "shared/value/ByteVecOperations.hpp"
#include "shared/value/Uuid.hpp"
#include <algorithm>
#include <stdexcept>

BinaryModificationDiff_t BinaryModificationDiff_t::add(binary_offset offset, const byte_vec& newBytes)
{
    return BinaryModificationDiff_t {
        CUuid { },
        BinaryModificationDiffType::ADD,
        offset,
        newBytes.size(),
        { },
        newBytes
    };
}

BinaryModificationDiff_t BinaryModificationDiff_t::remove(binary_offset offset, const byte_vec& oldBytes)
{
    return BinaryModificationDiff_t {
        CUuid { },
        BinaryModificationDiffType::REMOVE,
        offset,
        oldBytes.size(),
        oldBytes,
        { }
    };
}

CBinaryModification::CBinaryModification(
    const CUuid& id,
    BinaryModificationType type,
    const vec_diff& vecDiff,
    const std::vector<CUuid>& requiredModificationIds
):  m_id(id),
    m_type(type),
    m_vecDiff(vecDiff),
    m_requiredModificationIds(requiredModificationIds)
{
    if (m_vecDiff.size() == 0) {
        throw std::runtime_error(strenc("Diff cannot be empty"));
    }
}

CUuid CBinaryModification::id() const
{
    return m_id;
}

BinaryModificationType CBinaryModification::type() const
{
    return m_type;
}

std::vector<CUuid> CBinaryModification::requiredModificationIds() const
{
    return m_requiredModificationIds;
}

const byte_vec CBinaryModification::apply(byte_vec targetBytes) const
{
    auto infDiff = std::vector<diff::Diff> { };

    for (const auto& dmDiff : m_vecDiff) {
        if (dmDiff.type == BinaryModificationDiffType::ADD) {
            infDiff.push_back(diff::Diff { diff::EditType::Insert, dmDiff.offset, dmDiff.newBytes });
        } else if (dmDiff.type == BinaryModificationDiffType::REMOVE) {
            infDiff.push_back(diff::Diff { diff::EditType::Delete, dmDiff.offset, dmDiff.oldBytes });
        } else {
            throw ModificationException(strenc("Unexpected diff type"));
        }
    }

    return diff::patch(targetBytes, infDiff);
}

const binary_offset CBinaryModification::firstByteAddress() const
{
    std::optional<binary_offset> first = std::nullopt;
    for(const auto& diff : m_vecDiff) {
        if (first.has_value() == false) {
            first = diff.offset;
            continue;
        }
        const auto& value = first.value();
        if (value > diff.offset) {
            first = diff.offset;
        }
    }

    if (first.has_value() == false) {
        throw RuntimeException(strenc("Modification does not have any diff."));
    }

    return first.value();
}

const binary_offset CBinaryModification::firstByteAddressOfType(BinaryModificationDiffType type) const
{
    std::optional<binary_offset> first = std::nullopt;
    for(const auto& diff : m_vecDiff) {
        if (diff.type != type) {
            continue;
        }

        if (first.has_value() == false) {
            first = diff.offset;
            continue;
        }
        const auto& value = first.value();
        if (value > diff.offset) {
            first = diff.offset;
        }
    }

    if (first.has_value() == false) {
        throw RuntimeException(strenc("Modification does not have any diff of requested type."));
    }

    return first.value();
}

const binary_offset CBinaryModification::firstAddByteAddress() const
{
    return firstByteAddressOfType(BinaryModificationDiffType::ADD);
}

int CBinaryModification::totalSizeDiff() const
{
    int diffSize = 0;
    for(const auto& diff : m_vecDiff) {
        if (diff.type == BinaryModificationDiffType::ADD) {
            diffSize += diff.size;
        } else if (diff.type == BinaryModificationDiffType::REMOVE) {
            diffSize -= diff.size;
        }
    }

    return diffSize;
}

bool CBinaryModification::operator ==(const CBinaryModification& other) const
{
    return id() == other.id();
};

