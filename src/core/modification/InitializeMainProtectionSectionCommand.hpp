#pragma once

#include "core/file/BinaryFile.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include "shared/value/Uuid.hpp"

class CInitializeMainProtectionSectionCommand : public IModificationCommand
{
    const file_id m_fileId;
public:
    CInitializeMainProtectionSectionCommand(
        const file_id& fileId
    ):
        m_fileId(fileId)
    { }
    file_id fileId() const { return m_fileId; }
    CUuid modificationId() const { return { strenc("main_protection_section_init") }; }
    BinaryModificationType type() const { return BinaryModificationType::ADD_SECTION; }
};
