#pragma once

#include <core/file/BinaryFile.hpp>
#include <shared/message/IMessage.hpp>

class CFileUnloadedEvent : public IMessage
{
    file_id m_fileId;

public:
    CFileUnloadedEvent(const file_id fileId): m_fileId(fileId) { }
    file_id fileId() { return m_fileId; }
};

