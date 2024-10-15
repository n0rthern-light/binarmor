#ifndef CORE_MODIFICATION__ADD_BYTES_COMMAND_HPP_
#define CORE_MODIFICATION__ADD_BYTES_COMMAND_HPP_

#include "../file/BinaryFile.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/modification/ModificationCommand.hpp"
#include <optional>
#include <shared/value/Uuid.hpp>

namespace program::core::modification::bytes {
    class CAddBytesCommand : public IModificationCommand
    {
        const file::file_id m_fileId;
        const CUuid m_bytesId;
        const std::optional<std::string> m_sectionId;
        const byte_vec m_bytes;
        const bool m_executeOnStartup;
        const bool m_executable;
        const bool m_writeable;
        const std::vector<CUuid> m_requiredModificationIds;
    public:
        CAddBytesCommand(
            const file::file_id& fileId,
            const CUuid& bytesId,
            const std::optional<std::string>& sectionId,
            const byte_vec& bytes,
            bool executable = false,
            bool writeable = false,
            bool executeOnStartup = false,
            const std::vector<CUuid>& requiredModificationIds = { }
        ):  m_fileId(fileId),
            m_bytesId(bytesId),
            m_sectionId(sectionId),
            m_bytes(bytes),
            m_executable(executable),
            m_writeable(writeable),
            m_executeOnStartup(executeOnStartup),
            m_requiredModificationIds(requiredModificationIds)
        { }
        file::file_id fileId() const { return m_fileId; }
        CUuid bytesId() const { return m_bytesId; }
        file::BinaryModificationType type() const { return executable() ? file::BinaryModificationType::WRITE_CODE : file::BinaryModificationType::WRITE_DATA; } 
        CUuid modificationId() const { return bytesId(); }
        std::optional<std::string> sectionId() const { return m_sectionId; }
        byte_vec bytes() const { return m_bytes; }
        bool executeOnStartup() const { return m_executeOnStartup; }
        bool executable() const { return m_executable; }
        bool writeable() const { return m_writeable; }
        const std::vector<CUuid> requiredModificationIds() const { return m_requiredModificationIds; }
    };
}

#endif // CORE_MODIFICATION__ADD_BYTES_COMMAND_HPP_
