#include "AddImportHandler.hpp"
#include "core/file/BinaryFileStateManager.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/file/flags.hpp"
#include "core/format/ISection.hpp"
#include "core/modification/EncryptOriginalImportsCommand.hpp"
#include "core/modification/InitializeMainProtectionSectionCommand.hpp"
#include "core/modification/ModificationException.hpp"
#include "core/shared/attributes.hpp"
#include <memory>

CAddImportHandler::CAddImportHandler(
    CBinaryFileStateManager* fileManager,
    ICrypter* crypter,
    IMessageBus* commandBus
):
    m_fileManager(fileManager),
    m_crypter(crypter),
    m_commandBus(commandBus)
{ }

void CAddImportHandler::handle(const CAddImportCommand& command)
{
    // to add we need to hash / encrypt original import table + rename section
    // store original import table in buffer 
    // add new required imports to the buffer
    // unregister previous custom IAT if was there
    // write the buffer to the .binarmor section as IAT
    // modify headers to point to the new IAT
    auto binaryFile = m_fileManager->binaryFile(command.fileId());
    if (binaryFile == nullptr) {
        throw ModificationException(strenc("Binary file not found in memory"));
    }

    if (binaryFile->format() != Format::Windows_PE) {
        throw ModificationException(strenc("Only Windows PE is supported for adding imports"));
    }

    auto format = m_fileManager->binaryFileModifiedBinaryAsFormat(command.fileId());
    const auto import = format->import(command.moduleName(), command.functionName());

    if (import != nullptr) {
        return;
        //throw ModificationException("Import already registered");
    }
    
    if (binaryFile->hasFlags(BinaryFileFlags::HAS_ENCRYPTED_ORIGINAL_IMPORTS) == false) {
        m_commandBus->publish(
            std::make_shared<CEncryptOriginalImportsCommand>(command.fileId())
        );
    }

    if (binaryFile->hasFlags(BinaryFileFlags::HAS_MAIN_PROTECTION_SECTION_INITIALIZED) == false) {
        m_commandBus->publish(
            std::make_shared<CInitializeMainProtectionSectionCommand>(command.fileId())
        );
    }

    // add custom IAT
    // when working then make the command reusable so the previous custom IAT will be rebuilt if another import is added
    // fix all text/code section references to old imports to new ones

    format = m_fileManager->binaryFileModifiedBinaryAsFormat(command.fileId());
}
