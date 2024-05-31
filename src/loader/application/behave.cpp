#include "behave.hpp"
#include "container.hpp"
#include "events/NewFileSelectedEvent.hpp"
#include "events/UIRequestedOpenFileEvent.hpp"
#include <shared/application/container.hpp>
#include <core/application/container.hpp>
#include <core/file/analysis/exceptions/UnsupportedFileException.hpp>
#include <core/application/events/BinaryFileLoadedEvent.hpp>
#include <core/application/events/BinaryFileAnalyzedEvent.hpp>
#include <shared/self_obfuscation/strenc.hpp>

void program::loader::application::behave(int argc, char** argv)
{
    program::shared::container::eventBus->subscribe(typeid(CUIRequestedOpenFileEvent), [&](IMessage* event) {
        program::loader::container::guiApp->promptOpenFile();
	});

    program::shared::container::eventBus->subscribe(typeid(CNewFileSelectedEvent), [&](IMessage* event) {
		auto newFileSelectedEvent = dynamic_cast<CNewFileSelectedEvent*>(event);
        program::loader::container::guiApp->displayStatus(strenc("Opening a file: ") + newFileSelectedEvent->path() + strenc("..."));
        program::core::container::file::binaryFileStateManager->load(newFileSelectedEvent->path());
	});

    program::shared::container::eventBus->subscribe(typeid(CBinaryFileLoadedEvent), [&](IMessage* event) {
		auto binaryFile = program::core::container::file::binaryFileStateManager->binaryFile();
		try {
            program::core::container::file::analysis::runner->run(binaryFile.get());
		}
		catch (const UnsupportedFileException& e) {
            program::loader::container::guiApp->displayErrorMessageBox(strenc("Unsupported File Format"), strenc("Choosen file format is not supported."));
		}
	});

    program::shared::container::eventBus->subscribe(typeid(CBinaryFileAnalyzedEvent), [&](IMessage* event) {
        program::loader::container::guiApp->displayInfoMessageBox(strenc("Binary has been analyzed"), strenc("Success"));
		auto binaryFile = program::core::container::file::binaryFileStateManager->binaryFile();
        program::loader::container::guiApp->displayBinaryFile(*binaryFile.get());
        program::loader::container::guiApp->displayStatus(binaryFile->filePath());
	});
}

