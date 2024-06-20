#include "AddExecutableCodeHandler.hpp"
#include "core/modification/AddExecutableCodeCommand.hpp"
#include "core/modification/AddSectionCommand.hpp"
#include "core/modification/section/SectionPermissions.hpp"
#include "shared/message/IMessageBus.hpp"
#include "shared/value/Uuid.hpp"
#include <memory>

CAddExecutableCodeHandler::CAddExecutableCodeHandler(IMessageBus* messageBus): m_messageBus(messageBus) { }

void CAddExecutableCodeHandler::handle(const CAddExecutableCodeCommand& command) const
{
    bool specifiedExistingSection = command.sectionId().has_value();
    auto sectionId = specifiedExistingSection ? command.sectionId().value() : CUuid { };

    if (!specifiedExistingSection) {
        m_messageBus->publish(
            std::make_shared<CAddSectionCommand>(sectionId, command.fileId(), CSectionPermissions(SectionPermissionType::EXECUTE))
        );
    } else {
        // query for section
        // throw exception if not found
    }

    // append shellcode to the section
    // append code reference to the inmemory/inbinary repository
    if (command.executeOnStartup()) {
        // add to startup shellcodes
    }
    // flush ?
}
