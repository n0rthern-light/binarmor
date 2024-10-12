#include "behave.hpp"
#include "container.hpp"
#include <memory>
#include <shared/application/container.hpp>
#include "core/modification/AddBytesCommand.hpp"
#include "core/modification/AddImportCommand.hpp"
#include "core/modification/AddSectionCommand.hpp"
#include "core/modification/ChangeBytesCommand.hpp"
#include "core/modification/EncryptOriginalImportsCommand.hpp"
#include "core/modification/InitializeMainProtectionSectionCommand.hpp"
#include "core/modification/resize/BinarySizeChangedEvent.hpp"
#include "core/modification/resize/FixBinaryResizeCommand.hpp"
#include "core/modification/import/AddImportHandler.hpp"
#include "events/FileUnloadRequestedEvent.hpp"
#include "events/WorkFileChangeRequestedEvent.hpp"
#include "events/NewFileSelectedEvent.hpp"
#include "shared/message/IMessageBus.hpp"
#include <shared/RuntimeException.hpp>

void program::core::application::behave(int argc, char** argv)
{
    program::shared::container::eventBus->subscribe(typeid(CNewFileSelectedEvent), [&](message_ptr event) {
        auto castedEvent = std::dynamic_pointer_cast<CNewFileSelectedEvent>(event);
        program::core::container::file::binaryFileStateManager->load(castedEvent->path());
    });

    program::shared::container::eventBus->subscribe(typeid(CWorkFileChangeRequestedEvent), [&](message_ptr event) {
        auto castedEvent = std::dynamic_pointer_cast<CWorkFileChangeRequestedEvent>(event);
        program::core::container::file::binaryFileStateManager->setCurrentWorkFile(castedEvent->fileId());
    });

    program::shared::container::eventBus->subscribe(typeid(CFileUnloadRequestedEvent), [&](message_ptr event) {
        auto castedEvent = std::dynamic_pointer_cast<CFileUnloadRequestedEvent>(event);
        program::core::container::file::binaryFileStateManager->unload(castedEvent->fileId());
    });

    program::shared::container::eventBus->subscribe(typeid(CBinarySizeChangedEvent), [&](message_ptr event) {
        auto castedEvent = std::dynamic_pointer_cast<CBinarySizeChangedEvent>(event);
        program::shared::container::commandBus->publish(
            std::make_shared<CFixBinaryResizeCommand>(*castedEvent)
        );
    });

    program::shared::container::commandBus->subscribe(typeid(CAddSectionCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<CAddSectionCommand>(command);
        program::core::container::handler::addSectionHandler->handle(*castedCommand);
    });

    program::shared::container::commandBus->subscribe(typeid(CAddBytesCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<CAddBytesCommand>(command);
        program::core::container::handler::addBytesHandler->handle(*castedCommand);
    });

    program::shared::container::commandBus->subscribe(typeid(CChangeBytesCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<CChangeBytesCommand>(command);
        program::core::container::handler::changeBytesHandler->handle(*castedCommand);
    });

    program::shared::container::commandBus->subscribe(typeid(CAddImportCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<CAddImportCommand>(command);
        program::core::container::handler::addImportHandler->handle(*castedCommand);
    });

    program::shared::container::commandBus->subscribe(typeid(CEncryptOriginalImportsCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<CEncryptOriginalImportsCommand>(command);
        program::core::container::handler::encryptOriginalImportsHandler->handle(*castedCommand);
    });

    program::shared::container::commandBus->subscribe(typeid(CInitializeMainProtectionSectionCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<CInitializeMainProtectionSectionCommand>(command);
        program::core::container::handler::initializeMainProtectionSectionHandler->handle(*castedCommand);
    });

    program::shared::container::commandBus->subscribe(typeid(CFixBinaryResizeCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<CFixBinaryResizeCommand>(command);
        program::core::container::handler::fixBinaryResizeHandler->handle(*castedCommand);
    });
}

