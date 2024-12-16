#ifndef CORE_APPLICATION_EVENTS__FILE_LOADED_EVENT_HPP_
#define CORE_APPLICATION_EVENTS__FILE_LOADED_EVENT_HPP_

#include <shared/message/IMessage.hpp>
#include <core/file/BinaryFile.hpp>

namespace program::core::application::events {
    class CFileLoadedEvent : public program::shared::message::IMessage
    {
        program::core::file::file_id m_fileId;

    public:
        CFileLoadedEvent(const program::core::file::file_id& fileId): m_fileId(fileId) { }
        program::core::file::file_id fileId() { return m_fileId; }
    };
}

#endif // CORE_APPLICATION_EVENTS__FILE_LOADED_EVENT_HPP_
