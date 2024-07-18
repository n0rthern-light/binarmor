#include "AddBytesHandler.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "core/modification/AddSectionCommand.hpp"
#include "core/modification/AddStartupCodeCommand.hpp"
#include "core/modification/ModificationException.hpp"
#include "core/modification/ids.hpp"
#include "../../shared/SectionPermissions.hpp"
#include "shared/message/IMessageBus.hpp"
#include <memory>

CAddBytesHandler::CAddBytesHandler(
    IMessageBus* messageBus
):  m_messageBus(messageBus)
{ }

void CAddBytesHandler::handle(const CAddBytesCommand& command) const
{
    bool specifiedExistingSection = command.sectionId().has_value();
    auto sectionId = specifiedExistingSection ? command.sectionId().value() : std::string(modification::sectionName::MAIN);

    if (!specifiedExistingSection) {
        m_messageBus->publish(
            std::make_shared<CAddSectionCommand>(command.fileId(), sectionId, CSectionPermissions(SectionPermissionType::EXECUTE), 0x1000)
        );
    }

    /*
    auto section = m_sectionQuery->findById(command.fileId(), sectionId);
    if (!section.has_value()) {
        throw ModificationException(strenc("Section not found in file"));
    }

    CSection pSection = section.value();
    const auto bytesSize = command.bytes().size();
    if (pSection.spaceLeft().get() < bytesSize) {
        throw ModificationException(strenc("No space left in the section"));
    }
    const auto bytesOffset = pSection.firstFreeAddress();

    m_messageBus->publish(
        std::make_shared<CWriteBytesCommand>(command.fileId(), command.bytesId(), bytesOffset, command.bytes())
    );

    m_bytesRepository->save(CInsertedBytes {
        command.fileId(),
        sectionId,
        command.bytesId(),
        bytesOffset,
        as_32(bytesSize),
        command.executeOnStartup(),
        command.executable(),
    });

    if (command.executeOnStartup()) {
        m_messageBus->publish(
            std::make_shared<CAddStartupCodeCommand>(command.fileId(), command.bytesId())
        );
    }
    */
}
