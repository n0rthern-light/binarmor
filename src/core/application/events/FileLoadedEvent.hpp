#ifndef CORE_APPLICATION_EVENTS__BINARY_FILE_LOADED_EVENT_HPP_
#define CORE_APPLICATION_EVENTS__BINARY_FILE_LOADED_EVENT_HPP_

#include <shared/message/IMessage.hpp>
#include <core/file/BinaryFile.hpp>
#include <string>

class CFileLoadedEvent : public IMessage
{
    file_id m_fileId;

public:
    CFileLoadedEvent(const std::string& fileId): m_fileId(fileId) { }
    file_id fileId() { return m_fileId; }
};

#endif // CORE_APPLICATION_EVENTS__BINARY_FILE_LOADED_EVENT_HPP_
