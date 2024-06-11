#ifndef CORE_APPLICATION_EVENTS__DETECTED_UNSUPPORTED_FILE_EVENT_HPP_
#define CORE_APPLICATION_EVENTS__DETECTED_UNSUPPORTED_FILE_EVENT_HPP_

#include "../IMessage.hpp"
#include <string>

class CRuntimeExceptionOccuredEvent : public IMessage
{
    std::string m_message;
public:
    CRuntimeExceptionOccuredEvent(const std::string& message): m_message(message) { }
    std::string message() { return m_message; }
};

#endif // CORE_APPLICATION_EVENTS__DETECTED_UNSUPPORTED_FILE_EVENT_HPP_
