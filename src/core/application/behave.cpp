#include "behave.hpp"
#include "container.hpp"
#include <shared/application/container.hpp>
#include "core/application/events/DetectedUnsupportedFileEvent.hpp"
#include "events/NewFileSelectedEvent.hpp"
#include "events/BinaryFileLoadedEvent.hpp"
#include "../file/analysis/exceptions/UnsupportedFileException.hpp"

void program::core::application::behave(int argc, char** argv)
{
    program::shared::container::eventBus->subscribe(typeid(CNewFileSelectedEvent), [&](IMessage* event) {
		auto newFileSelectedEvent = dynamic_cast<CNewFileSelectedEvent*>(event);
        program::core::container::file::binaryFileStateManager->load(newFileSelectedEvent->path());
	});

    program::shared::container::eventBus->subscribe(typeid(CBinaryFileLoadedEvent), [&](IMessage* event) {
		auto binaryFile = program::core::container::file::binaryFileStateManager->binaryFile();
		try {
            program::core::container::file::analysis::runner->run(binaryFile.get());
		}
		catch (const UnsupportedFileException& e) {
            program::shared::container::eventBus->publish(new DetectedUnsupportedFileEvent());
		}
	});
}

