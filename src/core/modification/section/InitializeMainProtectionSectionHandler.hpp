#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/InitializeMainProtectionSectionCommand.hpp"
#include "shared/message/IMessageBus.hpp"

namespace program::core::modification::section {
    class CInitializeMainProtectionSectionHandler
    {
        file::CBinaryFileStateManager* m_binaryFileManager;
        IMessageBus* m_commandBus;
    public:
        CInitializeMainProtectionSectionHandler(IMessageBus* commandBus, file::CBinaryFileStateManager* binaryFileManager);
        void handle(const CInitializeMainProtectionSectionCommand& command);
    };
}
