#ifndef CORE_MODIFICATION_BYTES__ADD_BYTES_HANDLER_HPP_
#define CORE_MODIFICATION_BYTES__ADD_BYTES_HANDLER_HPP_

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "shared/message/IMessageBus.hpp"

namespace program::core::modification::bytes {
    class CAddBytesHandler
    {
        IMessageBus* m_commandBus;
        CBinaryFileStateManager* m_binaryFilesManager;
    public:
        CAddBytesHandler(
            IMessageBus* commandBus,
            CBinaryFileStateManager* binaryFileManager
        );
        void handle(const CAddBytesCommand& command) const;
    };
}

#endif // CORE_MODIFICATION_BYTES__ADD_BYTES_HANDLER_HPP_
