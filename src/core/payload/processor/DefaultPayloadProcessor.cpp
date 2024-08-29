#include "core/payload/processor/DefaultPayloadProcessor.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "shared/RuntimeException.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include <cassert>
#include <optional>

CDefaultPayloadProcessor::CDefaultPayloadProcessor(CBinaryFileStateManager* fileManager): m_fileManager(fileManager) { assert(fileManager != nullptr); }

const std::optional<CAddBytesCommand> CDefaultPayloadProcessor::next(const file_id& fileId, const IPayload* payload) const
{
    if (payload == nullptr) {
        throw RuntimeException(strenc("An actual payload must be provided"));
    }

    auto fileFormat = m_fileManager->binaryFileModifiedBinaryAsFormat(fileId);

    return std::nullopt;
}
