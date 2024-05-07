#include "SimpleEventBus.hpp"

void CSimpleEventBus::subscribe(const std::type_index& type, const std::function<void(IEvent*)>& listener) {
	std::lock_guard<std::mutex> lock(mtx);
	subscribers[type].push_back(listener);
}

void CSimpleEventBus::publish(IEvent* event) {
	std::vector<std::function<void(IEvent*)>> handlers;
	{
		std::lock_guard<std::mutex> lock(mtx);
		auto it = subscribers.find(typeid(*event));
		if (it != subscribers.end()) {
			handlers = it->second;
		}
	}
	for (auto& handler : handlers) {
		std::thread([=] { handler(event); }).detach();
	}
}
