#ifndef CORE_MODIFICATION__ADD_BYTES_COMMAND_HPP_
#define CORE_MODIFICATION__ADD_BYTES_COMMAND_HPP_

#include "../file/BinaryFile.hpp"
#include <optional>
#include <shared/message/IMessage.hpp>
#include <shared/value/Uuid.hpp>

class CAddBytesCommand : public IMessage
{
    const file_id m_fileId;
    const CUuid m_bytesId;
    const std::optional<std::string> m_sectionId;
    const byte_vec m_bytes;
    const bool m_executeOnStartup;
    const bool m_executable;
    const bool m_writeable;
public:
    CAddBytesCommand(
        const file_id& fileId,
        const CUuid& bytesId,
        const std::optional<std::string>& sectionId,
        const byte_vec& bytes,
        bool executable = false,
        bool writeable = false,
        bool executeOnStartup = false
    ):  m_fileId(fileId),
        m_bytesId(bytesId),
        m_sectionId(sectionId),
        m_bytes(bytes),
        m_executable(executable),
        m_writeable(writeable),
        m_executeOnStartup(executeOnStartup)
    { }
    file_id fileId() const { return m_fileId; }
    CUuid bytesId() const { return m_bytesId; }
    std::optional<std::string> sectionId() const { return m_sectionId; }
    byte_vec bytes() const { return m_bytes; }
    bool executeOnStartup() const { return m_executeOnStartup; }
    bool executable() const { return m_executable; }
    bool writeable() const { return m_writeable; }
};

#endif // CORE_MODIFICATION__ADD_BYTES_COMMAND_HPP_
