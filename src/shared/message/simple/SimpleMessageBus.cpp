#include "SimpleMessageBus.hpp"
#include "../../RuntimeException.hpp"
#include "../../self_obfuscation/strenc.hpp"

CSimpleMessageBus::CSimpleMessageBus(bool t_bCommandBusMode): m_bCommandBusMode(t_bCommandBusMode) { }

void CSimpleMessageBus::subscribe(const std::type_index& type, const std::function<void(IMessage*)>& listener) {
	std::lock_guard<std::mutex> lock(mtx);

    if (m_bCommandBusMode == true && subscribers[type].size() > 0) {
        throw new RuntimeException(strenc("Cannot register more than one subscriber when MessageBus in CommandBus mode!"));
    }

	subscribers[type].push_back(listener);
}

void CSimpleMessageBus::publish(IMessage* message) {
	std::vector<std::function<void(IMessage*)>> handlers;
	{
		std::lock_guard<std::mutex> lock(mtx);
		auto it = subscribers.find(typeid(*message));
		if (it != subscribers.end()) {
			handlers = it->second;
		}
	}
	for (auto& handler : handlers) {
		std::thread([=] { handler(message); }).detach();
	}
}

