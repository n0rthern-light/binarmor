#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/ChangeBytesCommand.hpp"

namespace program::core::modification::bytes {
    class CChangeBytesHandler
    {
        file::CBinaryFileStateManager* m_binaryFilesManager;
    public:
        CChangeBytesHandler(
            file::CBinaryFileStateManager* binaryFileManager
        );
        void handle(const CChangeBytesCommand& command) const;
    };
}
