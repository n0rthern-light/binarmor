#pragma once

#include "../IMessageBus.hpp"
#include <map>
#include <vector>
#include <mutex>

class CSimpleMessageBus : public IMessageBus {
    const bool m_bCommandBusMode;
    std::map<std::type_index, std::vector<std::function<void(IMessage*)>>> subscribers;
    std::mutex mtx;

public:
    CSimpleMessageBus(bool t_bCommandBusMode = false);
    void subscribe(const std::type_index& type, const std::function<void(IMessage*)>& listener) override;
    void publish(IMessage* message) override;
};

