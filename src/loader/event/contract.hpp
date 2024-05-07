#pragma once

#include "../headers.hpp"
#include "IEvent.hpp"
#include "IEventBus.hpp"

namespace event {
	extern std::shared_ptr<IEventBus> bus;
	void init();
};
