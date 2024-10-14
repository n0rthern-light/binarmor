#pragma once

#include "FixBinaryResizeCommand.hpp"
#include "core/file/BinaryFileStateManager.hpp"

namespace program::core::modification::resize {
    class CFixBinaryResizeHandler
    {
        CBinaryFileStateManager* m_fileManager;
    public:
        CFixBinaryResizeHandler(CBinaryFileStateManager* fileManager);
        void handle(const CFixBinaryResizeCommand& command);
    };
}

