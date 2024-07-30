#include "behave.hpp"
#include "container.hpp"
#include <shared/application/container.hpp>
#include "core/modification/AddSectionCommand.hpp"
#include "events/FileUnloadRequestedEvent.hpp"
#include "events/WorkFileChangeRequestedEvent.hpp"
#include "events/NewFileSelectedEvent.hpp"
#include "shared/message/IMessageBus.hpp"
#include <shared/RuntimeException.hpp>

void program::core::application::behave(int argc, char** argv)
{
    program::shared::container::eventBus->subscribe(typeid(CNewFileSelectedEvent), [&](message_ptr event) {
        auto castedEvent = dynamic_cast<CNewFileSelectedEvent*>(event.get());
        program::core::container::file::binaryFileStateManager->load(castedEvent->path());
    });

    program::shared::container::eventBus->subscribe(typeid(CWorkFileChangeRequestedEvent), [&](message_ptr event) {
        auto castedEvent = dynamic_cast<CWorkFileChangeRequestedEvent*>(event.get());
        program::core::container::file::binaryFileStateManager->setCurrentWorkFile(castedEvent->fileId());
    });

    program::shared::container::eventBus->subscribe(typeid(CFileUnloadRequestedEvent), [&](message_ptr event) {
        auto castedEvent = dynamic_cast<CFileUnloadRequestedEvent*>(event.get());
        program::core::container::file::binaryFileStateManager->unload(castedEvent->fileId());
    });

    program::shared::container::commandBus->subscribe(typeid(CAddSectionCommand), [&](message_ptr command) {
        auto castedCommand = dynamic_cast<CAddSectionCommand*>(command.get());
        program::core::container::handler::addSectionHandler->handle(*castedCommand);
    });
}

