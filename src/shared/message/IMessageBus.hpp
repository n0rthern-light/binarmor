#ifndef SRC_SHARED_MESSAGE__I_MESSAGE_BUS_HPP_
#define SRC_SHARED_MESSAGE__I_MESSAGE_BUS_HPP_





#include "IMessage.hpp"
#include <memory>
#include <functional>
#include <typeindex>

typedef std::shared_ptr<IMessage> message_ptr;

class IMessageBus
{
public:
    virtual ~IMessageBus() = default;
    virtual void subscribe(const std::type_index& type, const std::function<void(message_ptr)>& listener) = 0;
    virtual void publish(message_ptr message) = 0;
};




#endif // SRC_SHARED_MESSAGE__I_MESSAGE_BUS_HPP_
