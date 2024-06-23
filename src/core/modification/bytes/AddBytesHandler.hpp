#pragma once

#include "core/modification/AddBytesCommand.hpp"
#include "shared/message/IMessageBus.hpp"

class CAddBytesHandler
{
    IMessageBus* m_messageBus;
public:
    CAddBytesHandler(IMessageBus* messageBus);
    void handle(const CAddBytesCommand& command) const;
};
