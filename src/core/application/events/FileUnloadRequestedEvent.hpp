#pragma once

#include <core/file/BinaryFile.hpp>
#include <shared/message/IMessage.hpp>

class CFileUnloadRequestedEvent : public IMessage
{
    file_id m_fileId;
public:
    CFileUnloadRequestedEvent(const file_id& fileId): m_fileId(fileId) { }
    file_id fileId() { return m_fileId; }
};

