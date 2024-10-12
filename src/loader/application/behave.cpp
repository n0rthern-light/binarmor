#include "behave.hpp"
#include "container.hpp"
#include <core/application/events/FileUnloadedEvent.hpp>
#include <core/application/events/WorkFileChangeRequestedEvent.hpp>
#include "events/UIRequestedOpenFileEvent.hpp"
#include "shared/message/events/RuntimeExceptionOccuredEvent.hpp"
#include <core/application/events/WorkFileChangeRequestedEvent.hpp>
#include <core/application/events/NewFileSelectedEvent.hpp>
#include <memory>
#include <shared/application/container.hpp>
#include <core/application/container.hpp>
#include <core/application/events/FileLoadedEvent.hpp>
#include <shared/self_obfuscation/strenc.hpp>

void program::loader::application::behave(int argc, char** argv)
{
    program::shared::container::eventBus->subscribe(typeid(CRuntimeExceptionOccuredEvent), [&](message_ptr event) {
        auto castedEvent = std::dynamic_pointer_cast<CRuntimeExceptionOccuredEvent>(event);
        program::loader::container::guiApp->displayStatus(strenc("An problem occured: ") + castedEvent->message());
        program::loader::container::guiApp->displayErrorMessageBox(strenc("Oops!"), castedEvent->message());
    });

    program::shared::container::eventBus->subscribe(typeid(CUIRequestedOpenFileEvent), [&](message_ptr event) {
        program::loader::container::guiApp->promptOpenFile();
    });

    program::shared::container::eventBus->subscribe(typeid(CNewFileSelectedEvent), [&](message_ptr event) {
        auto castedEvent = std::dynamic_pointer_cast<CNewFileSelectedEvent>(event);
        program::loader::container::guiApp->displayStatus(strenc("Opening a file: ") + castedEvent->path() + strenc("..."));
    });

    program::shared::container::eventBus->subscribe(typeid(CFileLoadedEvent), [&](message_ptr event) {
        auto castedEvent = std::dynamic_pointer_cast<CFileLoadedEvent>(event);
        auto binaryFile = program::core::container::file::binaryFileStateManager->binaryFile(castedEvent->fileId());
        program::loader::container::guiApp->appendToLoadedFiles(binaryFile.get());
        program::loader::container::guiApp->highlightBinaryInFileList(castedEvent->fileId());
        program::loader::container::guiApp->displayBinaryFile(*binaryFile.get());
        program::loader::container::guiApp->displayStatus(strenc("File Loaded: ") + binaryFile->filePath().string());
    });

    program::shared::container::eventBus->subscribe(typeid(CWorkFileChangeRequestedEvent), [&](message_ptr event) {
        auto castedEvent = std::dynamic_pointer_cast<CWorkFileChangeRequestedEvent>(event);
        auto binaryFile = program::core::container::file::binaryFileStateManager->binaryFile(castedEvent->fileId());
        program::loader::container::guiApp->displayBinaryFile(*binaryFile.get());
    });

    program::shared::container::eventBus->subscribe(typeid(CFileUnloadedEvent), [&](message_ptr event) {
        auto castedEvent = std::dynamic_pointer_cast<CFileUnloadedEvent>(event);

        program::loader::container::guiApp->displayStatus(strenc("File ") + castedEvent->fileId() + strenc(" has been unloaded."));
        program::loader::container::guiApp->removeFromFileList(castedEvent->fileId());

        auto loadedFiles = program::core::container::file::binaryFileStateManager->loadedFiles();
        if (loadedFiles.empty()) {
            program::loader::container::guiApp->displayEmpty();
        } else {
            const auto fileId = loadedFiles.back();
            const auto binaryFile = program::core::container::file::binaryFileStateManager->binaryFile(fileId);

            program::loader::container::guiApp->highlightBinaryInFileList(fileId);
            program::loader::container::guiApp->displayBinaryFile(*binaryFile.get());
        }
    });
}

