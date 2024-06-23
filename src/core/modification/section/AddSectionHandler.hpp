#pragma once

#include "../AddSectionCommand.hpp"
#include "core/file/BinaryFileStateManager.hpp"

class CAddSectionHandler
{
    CBinaryFileStateManager* m_binaryFilesManager;
public:
    CAddSectionHandler(CBinaryFileStateManager* binaryFileManager);
    void handle(const CAddSectionCommand& command);
};

