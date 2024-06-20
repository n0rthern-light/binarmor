#pragma once

#include "../file/BinaryFile.hpp"
#include "core/assembler/defines.hpp"
#include <optional>
#include <shared/message/IMessage.hpp>
#include <shared/value/Uuid.hpp>

class CAddExecutableCodeCommand : public IMessage
{
    const CUuid m_codeId;
    const file_id m_fileId;
    const std::optional<CUuid> m_sectionId;
    const byte_vec m_shellcode;
    const bool m_executeOnStartup;

public:
    CAddExecutableCodeCommand(const CUuid& codeId, const file_id& fileId, const std::optional<CUuid>& sectionId, const byte_vec& shellcode, bool executeOnStartup): m_codeId(codeId), m_fileId(fileId), m_sectionId(sectionId), m_shellcode(shellcode), m_executeOnStartup(executeOnStartup) { }
    CUuid codeId() const { return m_codeId; }
    file_id fileId() const { return m_fileId; }
    std::optional<CUuid> sectionId() const { return m_sectionId; }
    byte_vec shellcode() const { return m_shellcode; }
    bool executeOnStartup() const { return m_executeOnStartup; }
};

