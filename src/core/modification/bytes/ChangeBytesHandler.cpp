#include "ChangeBytesHandler.hpp"
#include "core/file/BinaryFileStateManager.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/modification/ChangeBytesCommand.hpp"
#include "core/modification/ModificationException.hpp"
#include "core/file/diff/DiffExtractor.hpp"
#include "shared/value/ByteVecOperations.hpp"
#include <memory>

using namespace program::core::modification::bytes;
using namespace program::core::file;
using namespace program::shared::value;

CChangeBytesHandler::CChangeBytesHandler(
    CBinaryFileStateManager* binaryFilesManager
):
    m_binaryFilesManager(binaryFilesManager)
{ }

void CChangeBytesHandler::handle(const CChangeBytesCommand& command) const
{
    auto binaryFile = m_binaryFilesManager->binaryFile(command.fileId());
    if (binaryFile == nullptr) {
        throw ModificationException(strenc("Binary file not found in memory"));
    }

    auto fmt = binaryFile->modifiedBinaryAsFormat();
    const auto newBytes = CByteVecOperations::bytesModify(fmt->bytes(), command.offset(), command.bytes());
    auto fmtModified = fmt->changeBytes(newBytes);
    const auto diff = file::diff::CDiffExtractor::extract(fmt->bytes(), fmtModified->bytes()); 

    if (diff.size() == 0) {
        throw ModificationException(strenc("Could not change bytes, diff is zero."));
    }

    const auto modification = CBinaryModification {
        CUuid { command.bytesId() },
        command.type(),
        diff,
        command.requiredModificationIds()
    };

    binaryFile->registerModification(modification);
}
