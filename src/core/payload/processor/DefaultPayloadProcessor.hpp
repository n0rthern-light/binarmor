#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "core/payload/processor/PayloadProcessor.hpp"

class CDefaultPayloadProcessor : public IPayloadProcessor
{
    const CBinaryFileStateManager* m_fileManager;
public:
    CDefaultPayloadProcessor(CBinaryFileStateManager* fileManager);
    const std::optional<CAddBytesCommand> next(const file_id& fileId, const IPayload* payload) const;
};
