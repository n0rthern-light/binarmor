#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/ChangeBytesCommand.hpp"

class CChangeBytesHandler
{
    CBinaryFileStateManager* m_binaryFilesManager;
public:
    CChangeBytesHandler(
        CBinaryFileStateManager* binaryFileManager
    );
    void handle(const CChangeBytesCommand& command) const;
};
