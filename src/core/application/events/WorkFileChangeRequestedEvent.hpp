#ifndef CORE_APPLICATION_EVENTS__WORK_FILE_CHANGE_REQUESTED_EVENT_HPP_
#define CORE_APPLICATION_EVENTS__WORK_FILE_CHANGE_REQUESTED_EVENT_HPP_

#include <shared/message/IMessage.hpp>
#include <core/file/BinaryFile.hpp>
#include <string>

namespace program::core::application::events {
    class CWorkFileChangeRequestedEvent : public program::shared::message::IMessage
    {
        program::core::file::file_id m_fileId;
    public:
        CWorkFileChangeRequestedEvent(const std::string& fileId): m_fileId(fileId) { }
        program::core::file::file_id fileId() { return m_fileId; }
    };
}

#endif // CORE_APPLICATION_EVENTS__WORK_FILE_CHANGE_REQUESTED_EVENT_HPP_
