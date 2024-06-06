#pragma once

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

