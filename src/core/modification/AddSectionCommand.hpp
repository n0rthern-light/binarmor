#ifndef CORE_MODIFICATION__ADD_SECTION_COMMAND_HPP_
#define CORE_MODIFICATION__ADD_SECTION_COMMAND_HPP_

#include "core/file/BinaryFile.hpp"
#include "../shared/SectionPermissions.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "core/modification/ModificationException.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include "shared/types/defines.hpp"
#include "shared/value/Uuid.hpp"

namespace program::core::modification::section {
    class CAddSectionCommand : public IModificationCommand
    {
        const file::file_id m_fileId;
        const std::string m_sectionId;
        const CSectionPermissions m_permissions;
        const binary_offset m_size;

    public:
        CAddSectionCommand(
            const file::file_id& fileId,
            const std::string& sectionId,
            const CSectionPermissions& permissions,
            const binary_offset size
        ):
            m_fileId(fileId),
            m_sectionId(sectionId),
            m_permissions(permissions),
            m_size(size)
        {
            if (sectionId.size() > 7) {
                // due to Windows PE null terminated IMAGE_SECTION_HEADER->Name being of type uint_8 Name[8];
                throw ModificationException(strenc("Section name is max 7 chars"));
            }
        }
        file::file_id fileId() const { return m_fileId; }
        CUuid modificationId() const { return { sectionId() }; }
        file::BinaryModificationType type() const { return file::BinaryModificationType::ADD_SECTION; }
        std::string sectionId() const { return m_sectionId; }
        CSectionPermissions permissions() const { return m_permissions; }
        binary_offset size() const { return m_size; }
    };
}

#endif // CORE_MODIFICATION__ADD_SECTION_COMMAND_HPP_
