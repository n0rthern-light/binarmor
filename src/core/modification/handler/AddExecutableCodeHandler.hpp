#pragma once

#include "core/modification/AddExecutableCodeCommand.hpp"
#include "shared/message/IMessageBus.hpp"

class CAddExecutableCodeHandler
{
    IMessageBus* m_messageBus;

public:
    CAddExecutableCodeHandler(IMessageBus* messageBus);
    void handle(const CAddExecutableCodeCommand& command) const;
};
