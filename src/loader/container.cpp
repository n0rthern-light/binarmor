#include "container.hpp"
#include "ui/wx/wxWidgetsGuiApp.hpp"
#include "../shared/event/simple/SimpleEventBus.hpp"

std::shared_ptr<IEventBus> container::eventBus = nullptr;
std::shared_ptr<IGuiApp> container::guiApp = nullptr;

void container::init(int argc, char** argv, bool isTest)
{
	container::eventBus = std::make_shared<CSimpleEventBus>();

	if (!isTest) {
		container::guiApp = std::make_shared<CwxWidgetsGuiApp>(argc, argv);
	}
}
