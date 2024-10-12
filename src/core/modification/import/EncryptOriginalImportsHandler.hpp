#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/EncryptOriginalImportsCommand.hpp"
#include "shared/crypto/ICrypter.hpp"

class CEncryptOriginalImportsHandler
{
    const CBinaryFileStateManager* m_fileManager;
    const ICrypter* m_crypter;
public:
    CEncryptOriginalImportsHandler(CBinaryFileStateManager* fileManager, ICrypter* cryper);
    void handle(const CEncryptOriginalImportsCommand& command);
};
