#ifndef CORE_MODIFICATION__ADD_SECTION_COMMAND_HPP_
#define CORE_MODIFICATION__ADD_SECTION_COMMAND_HPP_

#include "core/file/BinaryFile.hpp"
#include "../shared/SectionPermissions.hpp"
#include "shared/message/IMessage.hpp"
#include "shared/types/defines.hpp"

class CAddSectionCommand : public IMessage
{
    const file_id m_fileId;
    const std::string m_sectionId;
    const CSectionPermissions m_permissions;
    const binary_offset m_size;

public:
    CAddSectionCommand(
        const file_id& fileId,
        const std::string& sectionId,
        const CSectionPermissions& permissions,
        const binary_offset size
    ):
        m_fileId(fileId),
        m_sectionId(sectionId),
        m_permissions(permissions),
        m_size(size)
    { }
    file_id fileId() const { return m_fileId; }
    std::string sectionId() const { return m_sectionId; }
    CSectionPermissions permissions() const { return m_permissions; }
    binary_offset size() const { return m_size; }
};

#endif // CORE_MODIFICATION__ADD_SECTION_COMMAND_HPP_
