#ifndef CORE_MODIFICATION_BYTES__ADD_BYTES_HANDLER_HPP_
#define CORE_MODIFICATION_BYTES__ADD_BYTES_HANDLER_HPP_

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "shared/message/IMessageBus.hpp"

namespace program::core::modification::bytes {
    class CAddBytesHandler
    {
        program::shared::message::IMessageBus* m_commandBus;
        file::CBinaryFileStateManager* m_binaryFilesManager;
    public:
        CAddBytesHandler(
            program::shared::message::IMessageBus* commandBus,
            file::CBinaryFileStateManager* binaryFileManager
        );
        void handle(const CAddBytesCommand& command) const;
    };
}

#endif // CORE_MODIFICATION_BYTES__ADD_BYTES_HANDLER_HPP_
