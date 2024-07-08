#include "BinaryModification.hpp"
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

BinaryModificationDiff_t BinaryModificationDiff_t::modify(binary_offset offset, const byte_vec& oldBytes, const byte_vec& newBytes)
{
    return BinaryModificationDiff_t {
        CUuid { },
        BinaryModificationDiffType::MODIFY,
        offset,
        newBytes.size(),
        oldBytes,
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
    for (const auto& diff : m_vecDiff) 
    {   
        switch (diff.type)
        {
            case BinaryModificationDiffType::REMOVE:
                targetBytes = CByteVecOperations::bytesRemove(targetBytes, diff.offset, diff.size);
                break;
            case BinaryModificationDiffType::ADD:
                targetBytes = CByteVecOperations::bytesInsert(targetBytes, diff.offset, diff.newBytes);
                break;
            case BinaryModificationDiffType::MODIFY:
                targetBytes = CByteVecOperations::bytesModify(targetBytes, diff.offset, diff.newBytes);
                break;
            default:
                throw std::runtime_error(strenc("Unsupported diff type"));
                break;
        }
    }
    
    return targetBytes;
}

const byte_vec CBinaryModification::revert(byte_vec targetBytes) const
{
    for (auto diff = m_vecDiff.rbegin(); diff != m_vecDiff.rend(); ++diff) {
        switch (diff->type)
        {
            case BinaryModificationDiffType::REMOVE:
                CByteVecOperations::bytesInsert(targetBytes, diff->offset, diff->oldBytes);
                break;
            case BinaryModificationDiffType::ADD:
                CByteVecOperations::bytesRemove(targetBytes, diff->offset, diff->newBytes.size());
                break;
            case BinaryModificationDiffType::MODIFY:
                CByteVecOperations::bytesModify(targetBytes, diff->offset, diff->oldBytes);
                break;
            default:
                throw std::runtime_error(strenc("Unsupported diff type"));
                break;
        }
    }
    
    return targetBytes;
}

bool CBinaryModification::operator ==(const CBinaryModification& other) const
{
    return id() == other.id();
};

