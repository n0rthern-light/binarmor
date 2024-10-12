#pragma once

#include "FixBinaryResizeCommand.hpp"
#include "core/file/BinaryFileStateManager.hpp"

class CFixBinaryResizeHandler
{
    CBinaryFileStateManager* m_fileManager;
public:
    CFixBinaryResizeHandler(CBinaryFileStateManager* fileManager);
    void handle(const CFixBinaryResizeCommand& command);
};
