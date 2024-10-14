#ifndef CORE_MODIFICATION_SECTION__ADD_SECTION_HANDLER_HPP_
#define CORE_MODIFICATION_SECTION__ADD_SECTION_HANDLER_HPP_

#include "../AddSectionCommand.hpp"
#include "core/file/BinaryFileStateManager.hpp"

namespace program::core::modification::section {
    class CAddSectionHandler
    {
        CBinaryFileStateManager* m_binaryFilesManager;
    public:
        CAddSectionHandler(CBinaryFileStateManager* binaryFileManager);
        void handle(const CAddSectionCommand& command);
    };
}

#endif // CORE_MODIFICATION_SECTION__ADD_SECTION_HANDLER_HPP_
