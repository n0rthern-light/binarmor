#pragma once

#include "core/file/BinaryFile.hpp"
#include "shared/message/IMessage.hpp"
#include "shared/types/defines.hpp"
#include "shared/value/Uuid.hpp"

namespace program::core::modification::resize {
    class CBinarySizeChangedEvent: public program::shared::message::IMessage
    {
        const file::file_id m_fileId;
        const program::shared::value::CUuid m_modificationId;
        const program::shared::types::binary_offset m_offset;
        const int m_diffSize;
    public:
        CBinarySizeChangedEvent(
            const file::file_id& fileId,
            const program::shared::value::CUuid& modificationId,
            const program::shared::types::binary_offset offset,
            const int diffSize
        ):
            m_fileId(fileId),
            m_modificationId(modificationId),
            m_offset(offset),
            m_diffSize(diffSize)
        { }

        file::file_id fileId() const { return m_fileId; }
        program::shared::value::CUuid modificationId() const { return m_modificationId; }
        program::shared::types::binary_offset offset() const { return m_offset; }
        int diffSize() const { return m_diffSize; }
    };
}
