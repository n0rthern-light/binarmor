#pragma once

#include "core/file/BinaryFile.hpp"
#include "shared/message/IMessage.hpp"
#include "shared/value/Uuid.hpp"

class CAddStartupCodeCommand : public IMessage
{
    const file_id m_fileId;
    const CUuid m_bytesId;
public:
    CAddStartupCodeCommand(const file_id& fileId, const CUuid& bytesId): m_fileId(fileId), m_bytesId(bytesId) { }
};

