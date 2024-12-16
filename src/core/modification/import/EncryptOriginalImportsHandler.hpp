#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/EncryptOriginalImportsCommand.hpp"
#include "shared/crypto/ICrypter.hpp"
#include <unistd.h>

namespace program::core::modification::encrypt {
    class CEncryptOriginalImportsHandler
    {
        const file::CBinaryFileStateManager* m_fileManager;
        const program::shared::crypto::ICrypter* m_crypter;
    public:
        CEncryptOriginalImportsHandler(file::CBinaryFileStateManager* fileManager, program::shared::crypto::ICrypter* cryper);
        void handle(const CEncryptOriginalImportsCommand& command);
    };
};
