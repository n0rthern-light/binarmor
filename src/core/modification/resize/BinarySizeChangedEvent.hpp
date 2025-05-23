#pragma once

#include "core/file/BinaryFile.hpp"
#include "shared/message/IMessage.hpp"
#include "shared/types/defines.hpp"
#include "shared/value/Uuid.hpp"

class CBinarySizeChangedEvent: public IMessage
{
    const file_id m_fileId;
    const CUuid m_modificationId;
    const binary_offset m_offset;
    const int m_diffSize;
public:
    CBinarySizeChangedEvent(
        const file_id& fileId,
        const CUuid& modificationId,
        const binary_offset offset,
        const int diffSize
    ):
        m_fileId(fileId),
        m_modificationId(modificationId),
        m_offset(offset),
        m_diffSize(diffSize)
    { }

    file_id fileId() const { return m_fileId; }
    CUuid modificationId() const { return m_modificationId; }
    binary_offset offset() const { return m_offset; }
    int diffSize() const { return m_diffSize; }
};
