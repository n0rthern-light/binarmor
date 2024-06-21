#pragma once

#include "../file/BinaryFile.hpp"
#include "core/modification/section/Section.hpp"
#include <optional>
#include <shared/message/IMessage.hpp>
#include <shared/value/Uuid.hpp>

class CAddBytesCommand : public IMessage
{
    const file_id m_fileId;
    const CUuid m_bytesId;
    const std::optional<section_id> m_sectionId;
    const byte_vec m_bytes;
    const bool m_executeOnStartup;
    const bool m_executable;
public:
    CAddBytesCommand(
        const file_id& fileId,
        const CUuid& bytesId,
        const std::optional<section_id>& sectionId,
        const byte_vec& bytes,
        bool executeOnStartup,
        bool executable
    ):  m_fileId(fileId),
        m_bytesId(bytesId),
        m_sectionId(sectionId),
        m_bytes(bytes),
        m_executeOnStartup(executeOnStartup),
        m_executable(executable)
    { }
    file_id fileId() const { return m_fileId; }
    CUuid bytesId() const { return m_bytesId; }
    std::optional<section_id> sectionId() const { return m_sectionId; }
    byte_vec bytes() const { return m_bytes; }
    bool executeOnStartup() const { return m_executeOnStartup; }
    bool executable() const { return m_executable; }
};

