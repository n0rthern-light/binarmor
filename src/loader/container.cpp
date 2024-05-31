#include "container.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <shared/event/simple/SimpleEventBus.hpp>
#include "ui/wx/wxWidgetsGuiApp.hpp"
#include "application/events/UIRequestedOpenFileEvent.hpp"
#include "application/events/NewFileSelectedEvent.hpp"
#include <core/file/fstream/fstreamFileReader.hpp>
#include <core/file/events/BinaryFileLoadedEvent.hpp>
#include <core/file/analysis/events/BinaryFileAnalyzedEvent.hpp>
#include <core/file/analysis/exceptions/UnsupportedFileException.hpp>

std::shared_ptr<IEventBus> container::eventBus = nullptr;
std::shared_ptr<IGuiApp> container::guiApp = nullptr;
std::shared_ptr<IFileReader> container::core::file::fileReader = nullptr;
std::shared_ptr<CBinaryFileStateManager> container::core::file::binaryFileStateManager = nullptr;
std::shared_ptr<CAnalysisRunner> container::core::file::analysis::runner = nullptr;

void container::init(int argc, char** argv)
{
    // register event -> command flow in /application/main.cpp or smth
    // then register command handlers as components one command = one handler / component / service
    // never subscribe to events in components /services
    // subscribe to events only in application definition and translate to commands
    //
    // components can only publish events
    // components cannot publish commands
    // components can only subscribe to commands
    // components cannot subscribe to events
    //
    // application can only publish commands
    // application cannot publish events
    // application can only subscribe to events
    // application cannot subscribe to commands
    //
	container::eventBus = std::make_shared<CSimpleEventBus>();
	container::guiApp = std::make_shared<CwxWidgetsGuiApp>(argc, argv, container::eventBus.get());
	container::core::file::fileReader = std::make_shared<CfstreamFileReader>();
	container::core::file::binaryFileStateManager = std::make_shared<CBinaryFileStateManager>(container::eventBus.get(), container::core::file::fileReader.get());
	container::core::file::analysis::runner = std::make_shared<CAnalysisRunner>(container::eventBus.get());

	container::eventBus->subscribe(typeid(CUIRequestedOpenFileEvent), [&](IEvent* event) {
		container::guiApp->promptOpenFile();
	});

	container::eventBus->subscribe(typeid(CNewFileSelectedEvent), [&](IEvent* event) {
		auto newFileSelectedEvent = dynamic_cast<CNewFileSelectedEvent*>(event);
		container::guiApp->displayStatus(strenc("Opening a file: ") + newFileSelectedEvent->path() + strenc("..."));
		container::core::file::binaryFileStateManager->load(newFileSelectedEvent->path());
	});

	container::eventBus->subscribe(typeid(CBinaryFileLoadedEvent), [&](IEvent* event) {
		auto binaryFile = container::core::file::binaryFileStateManager->binaryFile();
		try {
			container::core::file::analysis::runner->run(binaryFile.get());
		}
		catch (const UnsupportedFileException& e) {
			container::guiApp->displayErrorMessageBox(strenc("Unsupported File Format"), strenc("Choosen file format is not supported."));
		}
		container::guiApp->displayBinaryFile(*binaryFile.get());
		container::guiApp->displayStatus(binaryFile->filePath());
	});

	container::eventBus->subscribe(typeid(CBinaryFileAnalyzedEvent), [&](IEvent* event) {
		container::guiApp->displayInfoMessageBox(strenc("Binary has been analyzed"), strenc("Success"));
	});
}
