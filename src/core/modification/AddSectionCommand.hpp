#ifndef CORE_MODIFICATION__ADD_SECTION_COMMAND_HPP_
#define CORE_MODIFICATION__ADD_SECTION_COMMAND_HPP_

#include "core/file/BinaryFile.hpp"
#include "../shared/SectionPermissions.hpp"
#include "shared/message/IMessage.hpp"

class CAddSectionCommand : public IMessage
{
    const file_id m_fileId;
    const std::string m_sectionId;
    const CSectionPermissions m_permissions;

public:
    CAddSectionCommand(const file_id& fileId, const std::string& sectionId, const CSectionPermissions& permissions): m_fileId(fileId), m_sectionId(sectionId), m_permissions(permissions) { }
    file_id fileId() const { return m_fileId; }
    std::string sectionId() const { return m_sectionId; }
    CSectionPermissions permissions() const { return m_permissions; }
};

#endif // CORE_MODIFICATION__ADD_SECTION_COMMAND_HPP_
