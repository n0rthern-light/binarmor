#pragma once

#include <shared/message/IMessage.hpp>
#include <core/file/BinaryFile.hpp>
#include <string>

class CFileSelectedOnListEvent : public IMessage
{
    file_id m_fileId;
public:
    CFileSelectedOnListEvent(const std::string& fileId): m_fileId(fileId) { }
    file_id fileId() { return m_fileId; }
};

