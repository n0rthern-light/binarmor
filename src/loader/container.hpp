#pragma once

#include "headers.hpp"
#include "ui/IGuiApp.hpp"
#include <shared/event/IEventBus.hpp>

namespace container {
	extern std::shared_ptr<IEventBus> eventBus;
	extern std::shared_ptr<IGuiApp> guiApp;

	void init(int argc, char** argv, bool isTest = false);
}
