#include "container.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <shared/event/simple/SimpleEventBus.hpp>
#include "ui/wx/wxWidgetsGuiApp.hpp"
#include <core/file/UIRequestedOpenFile.hpp>
#include <core/file/NewFileSelected.hpp>
#include <core/file/fstream/fstreamFileReader.hpp>
#include <core/file/BinaryFileLoaded.hpp>

std::shared_ptr<IEventBus> container::eventBus = nullptr;
std::shared_ptr<IGuiApp> container::guiApp = nullptr;
std::shared_ptr<IFileReader> container::core::file::fileReader = nullptr;
std::shared_ptr<CBinaryFileStateManager> container::core::file::binaryFileStateManager = nullptr;

void container::init(int argc, char** argv)
{
	container::eventBus = std::make_shared<CSimpleEventBus>();
	container::guiApp = std::make_shared<CwxWidgetsGuiApp>(argc, argv, container::eventBus.get());
	container::core::file::fileReader = std::make_shared<CfstreamFileReader>();
	container::core::file::binaryFileStateManager = std::make_shared<CBinaryFileStateManager>(container::eventBus.get(), container::core::file::fileReader.get());

	container::eventBus->subscribe(typeid(CUIRequestedOpenFile), [&](IEvent* event) {
		container::guiApp->promptOpenFile();
	});

	container::eventBus->subscribe(typeid(CNewFileSelected), [&](IEvent* event) {
		auto newFileSelectedEvent = dynamic_cast<CNewFileSelected*>(event);
		container::guiApp->displayStatus(strenc("Opening a file: ") + newFileSelectedEvent->getPath() + strenc("..."));
		container::core::file::binaryFileStateManager->load(newFileSelectedEvent->getPath());
	});

	container::eventBus->subscribe(typeid(CBinaryFileLoaded), [&](IEvent* event) {
		container::guiApp->displayStatus(container::core::file::binaryFileStateManager->getBinaryFile()->getFilePath());
		container::guiApp->displayBinary(container::core::file::binaryFileStateManager->getBinaryFileBinary());
	});
}
