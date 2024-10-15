#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/AddImportsCommand.hpp"
#include "shared/crypto/ICrypter.hpp"
#include "shared/message/IMessageBus.hpp"


namespace program::core::modification::import {
    class CAddImportsHandler
    {
        const file::CBinaryFileStateManager* m_fileManager;
        const ICrypter* m_crypter;
        IMessageBus* m_commandBus;
    public:
        CAddImportsHandler(file::CBinaryFileStateManager* fileManager, ICrypter* cryper, IMessageBus* commandBus);
        void handle(const CAddImportsCommand& command);
    };
};

