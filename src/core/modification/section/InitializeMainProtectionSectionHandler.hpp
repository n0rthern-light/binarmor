#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/InitializeMainProtectionSectionCommand.hpp"
#include "shared/message/IMessageBus.hpp"

class CInitializeMainProtectionSectionHandler
{
    CBinaryFileStateManager* m_binaryFileManager;
    IMessageBus* m_commandBus;
public:
    CInitializeMainProtectionSectionHandler(IMessageBus* commandBus, CBinaryFileStateManager* binaryFileManager);
    void handle(const CInitializeMainProtectionSectionCommand& command);
};
