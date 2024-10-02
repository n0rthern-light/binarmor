#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/AddImportCommand.hpp"

class CAddImportHandler
{
    const CBinaryFileStateManager* m_fileManager;
public:
    CAddImportHandler(CBinaryFileStateManager* fileManager);
    void handle(const CAddImportCommand& command);
};
