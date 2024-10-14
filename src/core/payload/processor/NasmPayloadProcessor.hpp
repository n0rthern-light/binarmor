#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/format/IFormat.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "core/payload/IPayload.hpp"
#include "core/payload/processor/PayloadProcessor.hpp"
#include "shared/algo/DependencyGraph.hpp"
#include <memory>

namespace program::core::payload::nasm
{
    class CNasmPayloadProcessor : public IPayloadProcessor
    {
        const CBinaryFileStateManager* m_fileManager;
        const std::shared_ptr<program::core::modification::IModificationCommand> processImports(const file_id& fileId, const IPayload* payload) const;
        const CDependencyGraph buildDependencyGraph(const file_id& fileId, const IPayload* payload) const;
        const std::shared_ptr<program::core::modification::IModificationCommand> processData(const data_id& dataId, const file_id& fileId, const IPayload* payload) const;
        const std::shared_ptr<program::core::modification::IModificationCommand> processProcedure(const procedure_id& procedureId, const file_id& fileId, const IPayload* payload) const;
        const std::shared_ptr<program::core::modification::IModificationCommand> processPayloadChunks(const std::vector<std::string>& dependencies, const file_id& fileId, const IPayload* payload) const;
    public:
        CNasmPayloadProcessor(CBinaryFileStateManager* fileManager);
        const std::shared_ptr<program::core::modification::IModificationCommand> next(const file_id& fileId, const IPayload* payload) const;
    };
}
