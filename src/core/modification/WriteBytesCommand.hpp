#pragma once

#include "../file/BinaryFile.hpp"
#include "shared/value/Unsigned.hpp"
#include <shared/message/IMessage.hpp>
#include <shared/value/Uuid.hpp>

class CWriteBytesCommand : public IMessage
{
    const file_id m_fileId;
    const CUuid m_bytesId;
    const CUnsigned m_offset;
    const byte_vec m_bytes;

public:
    CWriteBytesCommand(
        const file_id& fileId,
        const CUuid& bytesId,
        const CUnsigned& offset,
        const byte_vec& bytes
    ):  m_fileId(fileId),
        m_bytesId(bytesId),
        m_offset(offset),
        m_bytes(bytes)
    { }
};

