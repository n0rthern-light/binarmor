#include "AddImportHandler.hpp"
#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/ModificationException.hpp"
#include "core/modification/diff/DiffExtractor.hpp"
#include <format>

CAddImportHandler::CAddImportHandler(CBinaryFileStateManager* fileManager):
    m_fileManager(fileManager)
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

    const auto format = m_fileManager->binaryFileModifiedBinaryAsFormat(command.fileId());
    const auto import = format->import(command.moduleName(), command.functionName());

    if (import != nullptr) {
        throw ModificationException(std::format(strenc("{} import already exists"), command.functionName()));
    }


    const auto modifiedFormat = format->addImport(command.moduleName(), command.functionName());
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
