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
        const program::shared::value::CUuid m_bytesId;
        const std::optional<std::string> m_sectionId;
        const program::shared::types::byte_vec m_bytes;
        const bool m_executeOnStartup;
        const bool m_executable;
        const bool m_writeable;
        const std::vector<program::shared::value::CUuid> m_requiredModificationIds;
    public:
        CAddBytesCommand(
            const file::file_id& fileId,
            const program::shared::value::CUuid& bytesId,
            const std::optional<std::string>& sectionId,
            const program::shared::types::byte_vec& bytes,
            bool executable = false,
            bool writeable = false,
            bool executeOnStartup = false,
            const std::vector<program::shared::value::CUuid>& requiredModificationIds = { }
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
        program::shared::value::CUuid bytesId() const { return m_bytesId; }
        file::BinaryModificationType type() const { return executable() ? file::BinaryModificationType::WRITE_CODE : file::BinaryModificationType::WRITE_DATA; } 
        program::shared::value::CUuid modificationId() const { return bytesId(); }
        std::optional<std::string> sectionId() const { return m_sectionId; }
        program::shared::types::byte_vec bytes() const { return m_bytes; }
        bool executeOnStartup() const { return m_executeOnStartup; }
        bool executable() const { return m_executable; }
        bool writeable() const { return m_writeable; }
        const std::vector<program::shared::value::CUuid> requiredModificationIds() const { return m_requiredModificationIds; }
    };
}

#endif // CORE_MODIFICATION__ADD_BYTES_COMMAND_HPP_
