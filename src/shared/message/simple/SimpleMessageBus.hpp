#ifndef SHARED_MESSAGE_SIMPLE__SIMPLE_MESSAGE_BUS_HPP_
#define SHARED_MESSAGE_SIMPLE__SIMPLE_MESSAGE_BUS_HPP_

#include "../IMessageBus.hpp"
#include <map>
#include <vector>
#include <mutex>

// typedef void (*handler_type)(void (*)(void));
using handler_type_fn = const std::function<void()>&;
using handler_type = std::function<void(handler_type_fn)>;
constexpr auto handler_type_sync = [](handler_type_fn f){ f(); };

class CSimpleMessageBus : public IMessageBus {
    handler_type m_handlerType;
    const bool m_bCommandBusMode;

    std::map<std::type_index, std::vector<std::function<void(message_ptr)>>> m_subscribers;
    std::mutex m_mtx;

public:
    CSimpleMessageBus(bool t_bCommandBusMode = false);
    void subscribe(const std::type_index& type, const std::function<void(message_ptr)>& listener) override;
    void publish(message_ptr message) override;
    void overrideHandlerType(const handler_type& handlerType);
};

#endif // SHARED_MESSAGE_SIMPLE__SIMPLE_MESSAGE_BUS_HPP_
