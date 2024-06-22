#pragma once

#include "core/file/BinaryFile.hpp"
#include "core/modification/section/Section.hpp"
#include "core/modification/section/SectionPermissions.hpp"
#include "shared/message/IMessage.hpp"
#include "shared/value/Uuid.hpp"

class CAddSectionCommand : public IMessage
{
    const file_id m_fileId;
    const section_id m_sectionId;
    const CSectionPermissions m_permissions;

public:
    CAddSectionCommand(const file_id& fileId, const section_id& sectionId, const CSectionPermissions& permissions): m_fileId(fileId), m_sectionId(sectionId), m_permissions(permissions) { }
    file_id fileId() const { return m_fileId; }
    section_id sectionId() const { return m_sectionId; }
    CSectionPermissions permissions() const { return m_permissions; }
};

