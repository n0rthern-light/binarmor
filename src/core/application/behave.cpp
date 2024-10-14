#include "behave.hpp"
#include "container.hpp"
#include <memory>
#include <shared/application/container.hpp>
#include "core/modification/AddBytesCommand.hpp"
#include "core/modification/AddImportsCommand.hpp"
#include "core/modification/AddSectionCommand.hpp"
#include "core/modification/ChangeBytesCommand.hpp"
#include "core/modification/EncryptOriginalImportsCommand.hpp"
#include "core/modification/InitializeMainProtectionSectionCommand.hpp"
#include "core/modification/resize/BinarySizeChangedEvent.hpp"
#include "core/modification/resize/FixBinaryResizeCommand.hpp"
#include "core/modification/import/AddImportsHandler.hpp"
#include "events/FileUnloadRequestedEvent.hpp"
#include "events/WorkFileChangeRequestedEvent.hpp"
#include "events/NewFileSelectedEvent.hpp"
#include "shared/message/IMessageBus.hpp"
#include <shared/RuntimeException.hpp>


using namespace program::core;

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

    program::shared::container::eventBus->subscribe(typeid(modification::resize::CBinarySizeChangedEvent), [&](message_ptr event) {
        auto castedEvent = std::dynamic_pointer_cast<modification::resize::CBinarySizeChangedEvent>(event);
        program::shared::container::commandBus->publish(
            std::make_shared<modification::resize::CFixBinaryResizeCommand>(*castedEvent)
        );
    });

    program::shared::container::commandBus->subscribe(typeid(modification::section::CAddSectionCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<modification::section::CAddSectionCommand>(command);
        program::core::container::handler::addSectionHandler->handle(*castedCommand);
    });

    program::shared::container::commandBus->subscribe(typeid(modification::bytes::CAddBytesCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<modification::bytes::CAddBytesCommand>(command);
        program::core::container::handler::addBytesHandler->handle(*castedCommand);
    });

    program::shared::container::commandBus->subscribe(typeid(modification::bytes::CChangeBytesCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<modification::bytes::CChangeBytesCommand>(command);
        program::core::container::handler::changeBytesHandler->handle(*castedCommand);
    });

    program::shared::container::commandBus->subscribe(typeid(modification::import::CAddImportsCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<modification::import::CAddImportsCommand>(command);
        program::core::container::handler::addImportsHandler->handle(*castedCommand);
    });

    program::shared::container::commandBus->subscribe(typeid(modification::encrypt::CEncryptOriginalImportsCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<modification::encrypt::CEncryptOriginalImportsCommand>(command);
        program::core::container::handler::encryptOriginalImportsHandler->handle(*castedCommand);
    });

    program::shared::container::commandBus->subscribe(typeid(modification::section::CInitializeMainProtectionSectionCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<modification::section::CInitializeMainProtectionSectionCommand>(command);
        program::core::container::handler::initializeMainProtectionSectionHandler->handle(*castedCommand);
    });

    program::shared::container::commandBus->subscribe(typeid(modification::resize::CFixBinaryResizeCommand), [&](message_ptr command) {
        auto castedCommand = std::dynamic_pointer_cast<modification::resize::CFixBinaryResizeCommand>(command);
        program::core::container::handler::fixBinaryResizeHandler->handle(*castedCommand);
    });
}

