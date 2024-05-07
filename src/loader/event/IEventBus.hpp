#pragma once

#include "IEvent.hpp"
#include "event_headers.hpp"

class IEventBus
{
public:
    virtual ~IEventBus() = default;
    virtual void subscribe(const std::type_index& type, const std::function<void(IEvent*)>& listener) = 0;
    virtual void publish(IEvent* event) = 0;
};

