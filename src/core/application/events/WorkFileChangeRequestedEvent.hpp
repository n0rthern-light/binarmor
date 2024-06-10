#pragma once

#include <shared/message/IMessage.hpp>
#include <core/file/BinaryFile.hpp>
#include <string>

class CWorkFileChangeRequestedEvent : public IMessage
{
    file_id m_fileId;
public:
    CWorkFileChangeRequestedEvent(const std::string& fileId): m_fileId(fileId) { }
    file_id fileId() { return m_fileId; }
};

