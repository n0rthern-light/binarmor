#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/AddImportsCommand.hpp"
#include "shared/crypto/ICrypter.hpp"
#include "shared/message/IMessageBus.hpp"


namespace program::core::modification::import {
    class CAddImportsHandler
    {
        const file::CBinaryFileStateManager* m_fileManager;
        const program::shared::crypto::ICrypter* m_crypter;
        program::shared::message::IMessageBus* m_commandBus;
    public:
        CAddImportsHandler(file::CBinaryFileStateManager* fileManager, program::shared::crypto::ICrypter* cryper, program::shared::message::IMessageBus* commandBus);
        void handle(const CAddImportsCommand& command);
    };
};

