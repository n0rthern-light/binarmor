#include "AddSectionHandler.hpp"
#include "core/modification/diff/DiffExtractor.hpp"
#include "core/shared/attributes.hpp"
#include "core/format/pe/PeFormat.hpp"
#include "core/modification/AddSectionCommand.hpp"
#include "core/modification/ModificationException.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include <memory>

CAddSectionHandler::CAddSectionHandler(CBinaryFileStateManager* binaryFileManager):
    m_binaryFilesManager(binaryFileManager) { }

void CAddSectionHandler::handle(const CAddSectionCommand& command)
{
    auto binaryFile = m_binaryFilesManager->binaryFile(command.fileId());
    if (binaryFile == nullptr) {
        throw ModificationException(strenc("Binary file not found in memory"));
    }

    const auto format = binaryFile->modifiedBinaryAsFormat();
    const auto modifiedFormat = format->addSection(command.sectionId(), command.size(), command.permissions());

    const auto diff = CDiffExtractor::extract(format->bytes(), modifiedFormat->bytes()); 

    if (diff.size() == 0) {
        throw ModificationException(strenc("Could not add new section, diff is zero."));
    }

    const auto modification = CBinaryModification {
        CUuid { command.sectionId() },
        BinaryModificationType::APPEND_SECTION,
        diff,
        { }
    };

    binaryFile->registerModification(modification);
}
