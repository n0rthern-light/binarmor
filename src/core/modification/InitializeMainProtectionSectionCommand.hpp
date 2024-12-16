#pragma once

#include "core/file/BinaryFile.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include "shared/value/Uuid.hpp"

namespace program::core::modification::section {
    class CInitializeMainProtectionSectionCommand : public IModificationCommand
    {
        const file::file_id m_fileId;
    public:
        CInitializeMainProtectionSectionCommand(
            const file::file_id& fileId
        ):
            m_fileId(fileId)
        { }
        file::file_id fileId() const { return m_fileId; }
        program::shared::value::CUuid modificationId() const { return { strenc("main_protection_section_init") }; }
        file::BinaryModificationType type() const { return file::BinaryModificationType::ADD_SECTION; }
    };
}
