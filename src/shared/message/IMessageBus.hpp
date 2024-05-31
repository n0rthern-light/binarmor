#pragma once

#include "IMessage.hpp"
#include "headers.hpp"

class IMessageBus
{
public:
    virtual ~IMessageBus() = default;
    virtual void subscribe(const std::type_index& type, const std::function<void(IMessage*)>& listener) = 0;
    virtual void publish(IMessage* message) = 0;
};

