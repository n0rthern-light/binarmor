#include "behave.hpp"
#include "container.hpp"
#include <shared/application/container.hpp>
#include "events/FileUnloadRequestedEvent.hpp"
#include "events/FileSelectedOnListEvent.hpp"
#include "events/NewFileSelectedEvent.hpp"

void program::core::application::behave(int argc, char** argv)
{
    program::shared::container::eventBus->subscribe(typeid(CNewFileSelectedEvent), [&](message_ptr event) {
		auto newFileSelectedEvent = dynamic_cast<CNewFileSelectedEvent*>(event.get());
        program::core::container::file::binaryFileStateManager->load(newFileSelectedEvent->path());
	});

    program::shared::container::eventBus->subscribe(typeid(CFileSelectedOnListEvent), [&](message_ptr event) {
		auto fileSelectedOnListEvent = dynamic_cast<CFileSelectedOnListEvent*>(event.get());
        program::core::container::file::binaryFileStateManager->setCurrent(fileSelectedOnListEvent->fileId());
	});

    program::shared::container::eventBus->subscribe(typeid(CFileUnloadRequestedEvent), [&](message_ptr event) {
		auto unloadRequestedEvent = dynamic_cast<CFileUnloadRequestedEvent*>(event.get());
        program::core::container::file::binaryFileStateManager->unload(unloadRequestedEvent->fileId());
	});
}

