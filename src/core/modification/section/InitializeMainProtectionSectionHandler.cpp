#include "InitializeMainProtectionSectionHandler.hpp"
#include "core/file/BinaryFileStateManager.hpp"
#include "core/file/flags.hpp"
#include "core/modification/InitializeMainProtectionSectionCommand.hpp"
#include "core/modification/AddSectionCommand.hpp"
#include "core/modification/ModificationException.hpp"
#include "core/modification/ids.hpp"
#include "core/shared/SectionPermissions.hpp"
#include "shared/message/IMessageBus.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include <memory>

using namespace program::core::modification::section;
using namespace program::core::file;

CInitializeMainProtectionSectionHandler::CInitializeMainProtectionSectionHandler(IMessageBus* commandBus, CBinaryFileStateManager* binaryFileManager):
    m_commandBus(commandBus), m_binaryFileManager(binaryFileManager) { }

void CInitializeMainProtectionSectionHandler::handle(const CInitializeMainProtectionSectionCommand& command)
{
    auto binaryFile = m_binaryFileManager->binaryFile(command.fileId());
    if (binaryFile == nullptr) {
        throw ModificationException(strenc("Binary file not found in memory"));
    }

    if (binaryFile->hasFlags(BinaryFileFlags::HAS_MAIN_PROTECTION_SECTION_INITIALIZED)) {
        throw ModificationException(strenc("Main protection section already initialized"));
    }

    m_commandBus->publish(std::make_shared<CAddSectionCommand>(
        command.fileId(),
        modification::sectionName::MAIN,
        program::core::shared::SectionPermissionType::EXECUTE,
        4096
    ));

    binaryFile->enableFlags(BinaryFileFlags::HAS_MAIN_PROTECTION_SECTION_INITIALIZED);
}

