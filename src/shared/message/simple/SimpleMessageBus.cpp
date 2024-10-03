#include "SimpleMessageBus.hpp"
#include "../events/RuntimeExceptionOccuredEvent.hpp"
#include "../../RuntimeException.hpp"
#include "../../self_obfuscation/strenc.hpp"

CSimpleMessageBus::CSimpleMessageBus(bool t_bCommandBusMode):
    m_handlerType(handler_type_sync),
    m_bCommandBusMode(t_bCommandBusMode)
{ }

void CSimpleMessageBus::subscribe(const std::type_index& type, const std::function<void(message_ptr)>& listener) {
    std::lock_guard<std::mutex> lock(m_mtx);

    if (m_bCommandBusMode == true && m_subscribers[type].size() > 0) {
        throw new RuntimeException(strenc("Cannot register more than one subscriber when MessageBus in CommandBus mode!"));
    }

    m_subscribers[type].push_back(listener);
}

void CSimpleMessageBus::publish(message_ptr message) {
    std::vector<std::function<void(message_ptr)>> handlers;
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        auto it = m_subscribers.find(typeid(*message));
        if (it != m_subscribers.end()) {
            handlers = it->second;
        }
    }
    for (auto& handler : handlers) {
        m_handlerType([&] {
            handler(message);
            /*
            try {
                handler(message);
            } catch (const RuntimeException& exception) {
                publish(std::make_shared<CRuntimeExceptionOccuredEvent>(exception.what()));
            }
            */
        });
    }
}

void CSimpleMessageBus::overrideHandlerType(const handler_type& handlerType)
{
    m_handlerType = handlerType;
}

