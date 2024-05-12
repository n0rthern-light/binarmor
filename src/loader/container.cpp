#include "container.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <shared/event/simple/SimpleEventBus.hpp>
#include "ui/wx/wxWidgetsGuiApp.hpp"
#include <core/file/UIRequestedOpenFileEvent.hpp>
#include <core/file/NewFileSelectedEvent.hpp>
#include <core/file/fstream/fstreamFileReader.hpp>
#include <core/file/BinaryFileLoadedEvent.hpp>
#include <core/file/analysis/BinaryFileAnalyzedEvent.hpp>
#include <core/file/analysis/UnsupportedFileException.hpp>

std::shared_ptr<IEventBus> container::eventBus = nullptr;
std::shared_ptr<IGuiApp> container::guiApp = nullptr;
std::shared_ptr<IFileReader> container::core::file::fileReader = nullptr;
std::shared_ptr<CBinaryFileStateManager> container::core::file::binaryFileStateManager = nullptr;
std::shared_ptr<CAnalysisRunner> container::core::file::attributes::runner = nullptr;

void container::init(int argc, char** argv)
{
	container::eventBus = std::make_shared<CSimpleEventBus>();
	container::guiApp = std::make_shared<CwxWidgetsGuiApp>(argc, argv, container::eventBus.get());
	container::core::file::fileReader = std::make_shared<CfstreamFileReader>();
	container::core::file::binaryFileStateManager = std::make_shared<CBinaryFileStateManager>(container::eventBus.get(), container::core::file::fileReader.get());
	container::core::file::attributes::runner = std::make_shared<CAnalysisRunner>(container::eventBus.get());

	container::eventBus->subscribe(typeid(CUIRequestedOpenFileEvent), [&](IEvent* event) {
		container::guiApp->promptOpenFile();
	});

	container::eventBus->subscribe(typeid(CNewFileSelectedEvent), [&](IEvent* event) {
		auto newFileSelectedEvent = dynamic_cast<CNewFileSelectedEvent*>(event);
		container::guiApp->displayStatus(strenc("Opening a file: ") + newFileSelectedEvent->getPath() + strenc("..."));
		container::core::file::binaryFileStateManager->load(newFileSelectedEvent->getPath());
	});

	container::eventBus->subscribe(typeid(CBinaryFileLoadedEvent), [&](IEvent* event) {
		auto binaryFile = container::core::file::binaryFileStateManager->getBinaryFile();
		try {
			container::core::file::attributes::runner->run(binaryFile.get());
		}
		catch (const UnsupportedFileException& e) {
			MessageBoxA(0, strenc("Choosen file format is not supported."), strenc("Unsupported File Format"), 0);
		}
		container::guiApp->displayBinary(binaryFile->getBinary());
		container::guiApp->displayStatus(binaryFile->getFilePath());
	});

	container::eventBus->subscribe(typeid(CBinaryFileAnalyzedEvent), [&](IEvent* event) {
		MessageBoxA(0, "Binary has been analyzed", "Success", 0);
	});
}
