#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/AddImportCommand.hpp"
#include "shared/crypto/ICrypter.hpp"
#include "shared/message/IMessageBus.hpp"

class CAddImportHandler
{
    const CBinaryFileStateManager* m_fileManager;
    const ICrypter* m_crypter;
    IMessageBus* m_commandBus;
public:
    CAddImportHandler(CBinaryFileStateManager* fileManager, ICrypter* cryper, IMessageBus* commandBus);
    void handle(const CAddImportCommand& command);
private:
};
