#ifndef CORE_APPLICATION_EVENTS__FILE_UNLOAD_REQUESTED_EVENT_HPP_
#define CORE_APPLICATION_EVENTS__FILE_UNLOAD_REQUESTED_EVENT_HPP_

#include <core/file/BinaryFile.hpp>
#include <shared/message/IMessage.hpp>

class CFileUnloadRequestedEvent : public IMessage
{
    file_id m_fileId;
public:
    CFileUnloadRequestedEvent(const file_id& fileId): m_fileId(fileId) { }
    file_id fileId() { return m_fileId; }
};

#endif // CORE_APPLICATION_EVENTS__FILE_UNLOAD_REQUESTED_EVENT_HPP_
