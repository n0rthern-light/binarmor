#pragma once

#include "core/file/BinaryFile.hpp"
#include "core/modification/section/SectionPermissions.hpp"
#include "shared/message/IMessage.hpp"
#include "shared/value/Uuid.hpp"

class CAddSectionCommand : public IMessage
{
    const CUuid m_sectionId;
    const file_id m_fileId;
    const CSectionPermissions permissions;
};

