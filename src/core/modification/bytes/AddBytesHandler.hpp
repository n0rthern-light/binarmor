#ifndef CORE_MODIFICATION_BYTES__ADD_BYTES_HANDLER_HPP_
#define CORE_MODIFICATION_BYTES__ADD_BYTES_HANDLER_HPP_

#include "core/modification/AddBytesCommand.hpp"
#include "shared/message/IMessageBus.hpp"

class CAddBytesHandler
{
    IMessageBus* m_messageBus;
public:
    CAddBytesHandler(IMessageBus* messageBus);
    void handle(const CAddBytesCommand& command) const;
};

#endif // CORE_MODIFICATION_BYTES__ADD_BYTES_HANDLER_HPP_
