#include "container.hpp"
#include <shared/event/simple/SimpleEventBus.hpp>
#include "ui/wx/wxWidgetsGuiApp.hpp"
#include <core/file/UIRequestedOpenFile.hpp>
#include <core/file/NewFileSelected.hpp>

std::shared_ptr<IEventBus> container::eventBus = nullptr;
std::shared_ptr<IGuiApp> container::guiApp = nullptr;

void container::init(int argc, char** argv)
{
	container::eventBus = std::make_shared<CSimpleEventBus>();
	container::guiApp = std::make_shared<CwxWidgetsGuiApp>(argc, argv, container::eventBus.get());

	container::eventBus->subscribe(typeid(CUIRequestedOpenFile), [&](IEvent* event) {
		container::guiApp->promptOpenFile();
	});

	container::eventBus->subscribe(typeid(CNewFileSelected), [&](IEvent* event) {
		auto newFileSelectedEvent = dynamic_cast<CNewFileSelected*>(event);
		MessageBoxA(0, newFileSelectedEvent->getPath().c_str(), "asdf", 0);
	});
}
