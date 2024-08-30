#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "core/payload/processor/PayloadProcessor.hpp"
#include <memory>

class CDefaultPayloadProcessor : public IPayloadProcessor
{
    const CBinaryFileStateManager* m_fileManager;
public:
    CDefaultPayloadProcessor(CBinaryFileStateManager* fileManager);
    const std::shared_ptr<IModificationCommand> next(const file_id& fileId, const IPayload* payload) const;
};
