#include "core/payload/processor/DefaultPayloadProcessor.hpp"
#include "core/file/BinaryFile.hpp"
#include "core/modification/AddImportCommand.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "shared/RuntimeException.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include <cassert>
#include <memory>

CDefaultPayloadProcessor::CDefaultPayloadProcessor(CBinaryFileStateManager* fileManager): m_fileManager(fileManager) { assert(fileManager != nullptr); }

const std::shared_ptr<IModificationCommand> CDefaultPayloadProcessor::next(const file_id& fileId, const IPayload* payload) const
{
    if (payload == nullptr) {
        throw RuntimeException(strenc("An actual payload must be provided"));
    }

    auto binaryFile = m_fileManager->binaryFile(fileId);

    if (binaryFile->format() != payload->format()) {
        throw RuntimeException(strenc("Payload and Binary format mismatch!"));
    }

    if (binaryFile->arch() != payload->architecture()) {
        throw RuntimeException(strenc("Payload and Binary architecture mismatch!"));
    }

    auto fileFormat = m_fileManager->binaryFileModifiedBinaryAsFormat(fileId);

    // imports are being processed always first
    for(const auto& requiredImport : payload->imports()) {
        const auto& import = fileFormat->import(requiredImport.moduleName, requiredImport.functionName);
        if (import == nullptr) {
            return std::make_shared<CAddImportCommand>(fileId, requiredImport.moduleName, requiredImport.functionName);
        }
    }

    // then not dependant data
    // then not dependant code
    // then dependant things
    // the things with the most dependencies last

    return nullptr;
}
