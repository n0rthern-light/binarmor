#ifndef CORE_APPLICATION_EVENTS__NEW_FILE_SELECTED_EVENT_HPP_
#define CORE_APPLICATION_EVENTS__NEW_FILE_SELECTED_EVENT_HPP_

#include <shared/message/IMessage.hpp>
#include <string>

class CNewFileSelectedEvent : public IMessage
{
    std::string _path;

public:
    CNewFileSelectedEvent(const char* path);
    const std::string& path();
};

#endif // CORE_APPLICATION_EVENTS__NEW_FILE_SELECTED_EVENT_HPP_
