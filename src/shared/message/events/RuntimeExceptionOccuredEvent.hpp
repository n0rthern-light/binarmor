#ifndef SHARED_MESSAGE_EVENTS__RUNTIME_EXCEPTION_OCCURED_EVENT_HPP_
#define SHARED_MESSAGE_EVENTS__RUNTIME_EXCEPTION_OCCURED_EVENT_HPP_

#include "../IMessage.hpp"
#include <string>

namespace program::shared::message::events
{
    class CRuntimeExceptionOccuredEvent : public IMessage
    {
        std::string m_message;
    public:
        CRuntimeExceptionOccuredEvent(const std::string& message): m_message(message) { }
        std::string message() { return m_message; }
    };
}

#endif // SHARED_MESSAGE_EVENTS__RUNTIME_EXCEPTION_OCCURED_EVENT_HPP_
