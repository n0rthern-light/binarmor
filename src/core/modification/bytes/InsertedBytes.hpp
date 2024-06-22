#pragma once

#include <shared/value/Unsigned.hpp>
#include <shared/value/Uuid.hpp>
#include "../../file/Binaryfile.hpp"
#include "core/modification/section/Section.hpp"

class CInsertedBytes
{
    const file_id m_fileId;
    const section_id m_sectionId;
    const CUuid m_id;
    const CUnsigned m_startAddress;
    const uint_32 m_size;
    const bool m_startup;
    const bool m_executable;
public:
    CInsertedBytes(
        const file_id& fileId,
        const section_id& sectionId,
        const CUuid& id,
        const CUnsigned& startAddress,
        const uint_32 size,
        const bool startup,
        const bool executable
    ):  m_fileId(fileId),
        m_sectionId(sectionId),
        m_id(id),
        m_startAddress(startAddress),
        m_size(size),
        m_startup(startup),
        m_executable(executable)
    { }
};
