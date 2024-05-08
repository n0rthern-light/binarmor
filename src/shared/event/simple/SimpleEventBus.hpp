#pragma once

#include "../IEventBus.hpp"

class CSimpleEventBus : public IEventBus {
    std::map<std::type_index, std::vector<std::function<void(IEvent*)>>> subscribers;
    std::mutex mtx;

public:
    void subscribe(const std::type_index& type, const std::function<void(IEvent*)>& listener) override;
    void publish(IEvent* event) override;
};
