#pragma once

#include "core/file/BinaryFile.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "shared/self_obfuscation/strenc.hpp"

namespace program::core::modification::encrypt {
    class CEncryptOriginalImportsCommand : public IModificationCommand
    {
        const file::file_id m_fileId;

    public:
        CEncryptOriginalImportsCommand(
            const file::file_id& fileId
        ):
            m_fileId(fileId)
        { }
        file::file_id fileId() const { return m_fileId; }
        program::shared::value::CUuid modificationId() const { return { std::format(strenc("encrypt_imports:{}"), m_fileId) }; }
        file::BinaryModificationType type() const { return file::BinaryModificationType::ENCRYPT_OLD_IMPORT; }
    };
}

