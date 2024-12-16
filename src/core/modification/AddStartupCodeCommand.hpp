#ifndef CORE_MODIFICATION__ADD_STARTUP_CODE_COMMAND_HPP_
#define CORE_MODIFICATION__ADD_STARTUP_CODE_COMMAND_HPP_

#include "core/file/BinaryFile.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "shared/value/Uuid.hpp"

namespace program::core::modification::code {
    class CAddStartupCodeCommand : public IModificationCommand
    {
        const file_id m_fileId;
        const CUuid m_bytesId;
    public:
        CAddStartupCodeCommand(const file_id& fileId, const CUuid& bytesId): m_fileId(fileId), m_bytesId(bytesId) { }
        file_id fileId() const { return m_fileId; }
        CUuid modificationId() const { return m_bytesId; }
        BinaryModificationType type() const { return BinaryModificationType::INIT_STARTUP_CODE; }
    };
}

#endif // CORE_MODIFICATION__ADD_STARTUP_CODE_COMMAND_HPP_
