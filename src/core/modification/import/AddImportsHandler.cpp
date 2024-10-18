#include "AddImportsHandler.hpp"
#include "core/file/BinaryFileStateManager.hpp"
#include "core/file/flags.hpp"
#include "core/modification/AddImportsCommand.hpp"
#include "core/modification/EncryptOriginalImportsCommand.hpp"
#include "core/modification/InitializeMainProtectionSectionCommand.hpp"
#include "core/modification/ModificationException.hpp"
#include "core/shared/attributes.hpp"
#include <memory>

using namespace program::core::modification::import;
using namespace program::core::modification::encrypt;
using namespace program::core::file;
using namespace program::core::shared;
using namespace program::shared::crypto;
using namespace program::shared::message;

CAddImportsHandler::CAddImportsHandler(
    CBinaryFileStateManager* fileManager,
    ICrypter* crypter,
    IMessageBus* commandBus
):
    m_fileManager(fileManager),
    m_crypter(crypter),
    m_commandBus(commandBus)
{ }

void CAddImportsHandler::handle(const CAddImportsCommand& command)
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
    auto filteredImports = import_pair_vec_t { };

    for(const auto& importReq : command.imports()) {
        const std::string& importModuleName = std::get<0>(importReq);
        const std::string& importFunctionName = std::get<1>(importReq);

        const auto import = format->import(importModuleName, importFunctionName);

        if (import == nullptr) {
            filteredImports.push_back({ importModuleName, importFunctionName });
        }
    }

    if (filteredImports.empty() == true) {
        return;
    }
    
    if (binaryFile->hasFlags(BinaryFileFlags::HAS_ENCRYPTED_ORIGINAL_IMPORTS) == false) {
        m_commandBus->publish(
            std::make_shared<encrypt::CEncryptOriginalImportsCommand>(command.fileId())
        );
    }

    if (binaryFile->hasFlags(BinaryFileFlags::HAS_MAIN_PROTECTION_SECTION_INITIALIZED) == false) {
        m_commandBus->publish(
            std::make_shared<section::CInitializeMainProtectionSectionCommand>(command.fileId())
        );
    }

    // add custom IAT
    // when working then make the command reusable so the previous custom IAT will be rebuilt if another import is added
    // fix all text/code section references to old imports to new ones

    format = m_fileManager->binaryFileModifiedBinaryAsFormat(command.fileId());
}
