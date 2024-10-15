#pragma once

#include "FixBinaryResizeCommand.hpp"
#include "core/file/BinaryFileStateManager.hpp"

namespace program::core::modification::resize {
    class CFixBinaryResizeHandler
    {
        file::CBinaryFileStateManager* m_fileManager;
    public:
        CFixBinaryResizeHandler(file::CBinaryFileStateManager* fileManager);
        void handle(const CFixBinaryResizeCommand& command);
    };
}

