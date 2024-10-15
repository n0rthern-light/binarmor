#pragma once

#include "../file/BinaryFile.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "shared/types/defines.hpp"
#include <shared/value/Uuid.hpp>

namespace program::core::modification::bytes {
    class CChangeBytesCommand : public IModificationCommand
    {
        const file::file_id m_fileId;
        const CUuid m_bytesId;
        const binary_offset m_offset;
        const byte_vec m_bytes;
        const file::BinaryModificationType m_modificationType;
        const std::vector<CUuid> m_requiredModificationIds;
    public:
        CChangeBytesCommand(
            const file::file_id& fileId,
            const CUuid& bytesId,
            const binary_offset offset,
            const byte_vec& bytes,
            const file::BinaryModificationType modificationType,
            const std::vector<CUuid>& requiredModificationIds = { }
        ):  m_fileId(fileId),
            m_bytesId(bytesId),
            m_offset(offset),
            m_bytes(bytes),
            m_modificationType(modificationType),
            m_requiredModificationIds(requiredModificationIds)
        { }
        file::file_id fileId() const { return m_fileId; }
        CUuid bytesId() const { return m_bytesId; }
        file::BinaryModificationType type() const { return m_modificationType; } 
        binary_offset offset() const { return m_offset; }
        CUuid modificationId() const { return bytesId(); }
        byte_vec bytes() const { return m_bytes; }
        const std::vector<CUuid> requiredModificationIds() const { return m_requiredModificationIds; }
    };
}
