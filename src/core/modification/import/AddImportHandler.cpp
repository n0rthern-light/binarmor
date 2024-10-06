#include "AddImportHandler.hpp"
#include "core/file/BinaryFileStateManager.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/format/pe/PeFormat.hpp"
#include "core/modification/ChangeBytesCommand.hpp"
#include "core/modification/ModificationException.hpp"
#include "core/modification/diff/DiffExtractor.hpp"
#include "core/shared/attributes.hpp"
#include "shared/types/defines.hpp"
#include <memory>
#include <tuple>

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

    const auto format = m_fileManager->binaryFileModifiedBinaryAsFormat(command.fileId());
    const auto peFormat = std::dynamic_pointer_cast<CPeFormat>(format);
    const auto import = format->import(command.moduleName(), command.functionName());

    if (import != nullptr) {
        throw ModificationException("Import already registered");
    }
    
    // todo extract and test encrypt original imports as a separate command + command handler

    // encrypt original imports definition
    for (const auto& module : format->importModules()) {
        for (const auto& import : module.second->imports()) {
            size_t i = 0;
            for (const auto& importDef : import->definitions()) {
                m_commandBus->publish(
                    std::make_shared<CChangeBytesCommand>(
                        command.fileId(),
                        CUuid { },
                        peFormat->rvaToOffset(importDef.rva),
                        byte_vec(importDef.size, i),
                        BinaryModificationType::ENCRYPT_OLD_IMPORT
                    )
                );
                ++i;
            }
        }

        m_commandBus->publish(
            std::make_shared<CChangeBytesCommand>(
                command.fileId(),
                CUuid { },
                peFormat->rvaToOffset(module.second->definitionRva()),
                byte_vec(module.second->definitionSize(), 0x01),
                BinaryModificationType::ENCRYPT_OLD_IMPORT
            )
        );
    }

    const auto modifiedFormat = format->changeBytes({});
    const auto diff = CDiffExtractor::extract(format->bytes(), modifiedFormat->bytes()); 

    if (diff.size() == 0) {
        throw ModificationException(strenc("Could not add new section, diff is zero."));
    }

    const auto modification = CBinaryModification {
        command.modificationId(),
        BinaryModificationType::WRITE_IMPORT,
        diff,
        { }
    };

    binaryFile->registerModification(modification);
}
