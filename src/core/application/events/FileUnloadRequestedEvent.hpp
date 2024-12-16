#ifndef CORE_APPLICATION_EVENTS__FILE_UNLOAD_REQUESTED_EVENT_HPP_
#define CORE_APPLICATION_EVENTS__FILE_UNLOAD_REQUESTED_EVENT_HPP_

#include <core/file/BinaryFile.hpp>
#include <shared/message/IMessage.hpp>

namespace program::core::application::events {
    class CFileUnloadRequestedEvent : public program::shared::message::IMessage
    {
        program::core::file::file_id m_fileId;
    public:
        CFileUnloadRequestedEvent(const program::core::file::file_id& fileId): m_fileId(fileId) { }
        program::core::file::file_id fileId() { return m_fileId; }
    };
}

#endif // CORE_APPLICATION_EVENTS__FILE_UNLOAD_REQUESTED_EVENT_HPP_
