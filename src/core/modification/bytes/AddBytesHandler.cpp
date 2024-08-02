#include "AddBytesHandler.hpp"
#include "core/file/BinaryFileStateManager.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/format/IFormat.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "core/modification/AddSectionCommand.hpp"
#include "core/modification/ModificationException.hpp"
#include "core/modification/diff/DiffExtractor.hpp"
#include "core/modification/ids.hpp"
#include "../../shared/SectionPermissions.hpp"
#include "shared/message/IMessageBus.hpp"
#include "shared/value/ByteVecOperations.hpp"
#include <memory>

CAddBytesHandler::CAddBytesHandler(
    IMessageBus* commandBus,
    CBinaryFileStateManager* binaryFilesManager
):
    m_commandBus(commandBus),
    m_binaryFilesManager(binaryFilesManager)
{ }

void CAddBytesHandler::handle(const CAddBytesCommand& command) const
{
    auto binaryFile = m_binaryFilesManager->binaryFile(command.fileId());
    if (binaryFile == nullptr) {
        throw ModificationException(strenc("Binary file not found in memory"));
    }

    bool specifiedExistingSection = command.sectionId().has_value();
    auto requestedSectionId = specifiedExistingSection ? command.sectionId().value() : std::string(modification::sectionName::MAIN);
    auto requestedPermissions = CSectionPermissions { };
    if (command.executable()) {
        requestedPermissions = requestedPermissions.withPermission(SectionPermissionType::EXECUTE);
    } else if (command.writeable()) {
        requestedPermissions = requestedPermissions.withPermission(SectionPermissionType::WRITE);
    }

    bool requestedSectionExists = false;
    auto fmt = binaryFile->modifiedBinaryAsFormat();
    for (const auto& section : fmt->sections()) {
        if (section->name() != requestedSectionId) {
            continue;
        }

        if (section->permissions() != requestedPermissions) {
            throw ModificationException(strenc("Requested section permissions doesnt match requirements"));
        }

        requestedSectionExists = true;
        break;
    }

    if (requestedSectionExists == false) {
        m_commandBus->publish(
            std::make_shared<CAddSectionCommand>(
                command.fileId(),
                requestedSectionId,
                requestedPermissions,
                command.bytes().size()
            )
        );

        fmt = binaryFile->modifiedBinaryAsFormat();
    }

    format_ptr fmtModified = nullptr;
    for(const auto& section : fmt->sections()) {
        if (section->name() != requestedSectionId) {
            continue;
        }

        const auto sectionOffset = section->baseAddress().get();
        const auto sectionSize = section->size();
        const auto sectionBytes = fmt->binary().part(sectionOffset, sectionSize).bytes();
        const auto requiredSize = command.bytes().size();
        binary_offset sectionFirstFreeOffset = 0;
        bool inserted = false;

        while(sectionFirstFreeOffset < sectionBytes.size() && !inserted) {
            binary_offset currentStreak = 0;
            while(
                sectionFirstFreeOffset + currentStreak < sectionBytes.size() &&
                sectionBytes[sectionFirstFreeOffset + currentStreak] == section->nullByteRepresentation() &&
                currentStreak < requiredSize
            ) {
                ++currentStreak;
            }

            if (currentStreak >= requiredSize && !inserted) {
                const auto finalOffset = sectionOffset + sectionFirstFreeOffset;
                if (fmt->binary().offsetExists(finalOffset) == false) {
                    throw ModificationException(strenc("Not found empty space in requested section."));
                }

                auto peBytes = fmt->bytes();
                peBytes = CByteVecOperations::bytesModify(peBytes, finalOffset, command.bytes());

                fmtModified = fmt->changeBytes(peBytes);
                inserted = true;
                break;
            }

            ++sectionFirstFreeOffset;
        }
    }

    if (fmtModified == nullptr) {
        throw ModificationException(strenc("Could not add bytes to the requested section"));
    }

    const auto diff = CDiffExtractor::extract(fmt->bytes(), fmtModified->bytes()); 

    if (diff.size() == 0) {
        throw ModificationException(strenc("Could not add bytes, diff is zero."));
    }

    const auto modification = CBinaryModification {
        CUuid { command.bytesId() },
        command.executable() ? BinaryModificationType::WRITE_CODE : BinaryModificationType::WRITE_DATA,
        diff,
        { }
    };

    binaryFile->registerModification(modification);
}
