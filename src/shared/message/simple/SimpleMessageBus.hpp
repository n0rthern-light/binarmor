#pragma once

#include "../IMessageBus.hpp"
#include <map>
#include <vector>
#include <mutex>

class CSimpleMessageBus : public IMessageBus {
    const bool m_bCommandBusMode;
    std::map<std::type_index, std::vector<std::function<void(message_ptr)>>> m_subscribers;
    std::mutex m_mtx;

public:
    CSimpleMessageBus(bool t_bCommandBusMode = false);
    void subscribe(const std::type_index& type, const std::function<void(message_ptr)>& listener) override;
    void publish(message_ptr message) override;
};

