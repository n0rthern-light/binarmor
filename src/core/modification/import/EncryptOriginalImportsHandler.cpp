#include "EncryptOriginalImportsHandler.hpp"
#include "core/file/BinaryFileStateManager.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/file/flags.hpp"
#include "core/format/pe/PeFormat.hpp"
#include "core/modification/EncryptOriginalImportsCommand.hpp"
#include "core/modification/ModificationException.hpp"
#include "core/file/diff/DiffExtractor.hpp"
#include "core/shared/attributes.hpp"
#include "shared/types/defines.hpp"
#include "shared/value/ByteVecOperations.hpp"
#include <memory>

using namespace program::core::modification::encrypt;
using namespace program::core::file::diff;
using namespace program::core::file;

CEncryptOriginalImportsHandler::CEncryptOriginalImportsHandler(
    CBinaryFileStateManager* fileManager,
    ICrypter* crypter
):
    m_fileManager(fileManager),
    m_crypter(crypter)
{ }

void CEncryptOriginalImportsHandler::handle(const CEncryptOriginalImportsCommand& command)
{
    auto binaryFile = m_fileManager->binaryFile(command.fileId());
    if (binaryFile == nullptr) {
        throw ModificationException(strenc("Binary file not found in memory"));
    }

    if (binaryFile->format() != Format::Windows_PE) {
        throw ModificationException(strenc("Only Windows PE is supported for adding imports"));
    }

    const auto format = m_fileManager->binaryFileModifiedBinaryAsFormat(command.fileId());
    const auto peFormat = std::dynamic_pointer_cast<CPeFormat>(format);
    
    if (binaryFile->hasFlags(BinaryFileFlags::HAS_ENCRYPTED_ORIGINAL_IMPORTS) == true) {
        throw ModificationException("Imports already encrypted");
    }

    // encrypt original imports definition
    const auto key = strenc("0dd6bd77151c480798c81c3a7fcf43bf");

    auto modifiedBytes = format->bytes();
    for (const auto& module : format->importModules()) {
        for (const auto& import : module.second->imports()) {
            size_t i = 0;
            for (const auto& importDef : import->definitions()) {
                const auto offset = peFormat->rvaToOffset(importDef.rva); 
                const auto originalBytes = (CBinary { modifiedBytes }).part(offset, importDef.size).bytes();
                const auto xoredBytes = m_crypter->xorBytes(originalBytes, key);

                modifiedBytes = CByteVecOperations::bytesModify(modifiedBytes, offset, xoredBytes);

                ++i;
            }
        }

        const auto moduleRva = module.second->definitionRva();
        const auto moduleSize = module.second->definitionSize();
        const auto moduleOffset = peFormat->rvaToOffset(moduleRva); 

        const auto moduleOriginalBytes = (CBinary { modifiedBytes }).part(moduleRva, moduleSize).bytes();
        const auto moduleXoredBytes = m_crypter->xorBytes(moduleOriginalBytes, key);


        modifiedBytes = CByteVecOperations::bytesModify(modifiedBytes, moduleOffset, moduleXoredBytes);
    }

    const auto diff = CDiffExtractor::extract(format->bytes(), modifiedBytes); 

    if (diff.size() == 0) {
        throw ModificationException(strenc("Could not add new section, diff is zero."));
    }

    const auto modification = CBinaryModification {
        command.modificationId(),
        command.type(),
        diff,
        { }
    };

    binaryFile->registerModification(modification);
    binaryFile->enableFlags(BinaryFileFlags::HAS_ENCRYPTED_ORIGINAL_IMPORTS);
}
