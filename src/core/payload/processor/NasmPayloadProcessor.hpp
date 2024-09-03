#pragma once

#include "core/file/BinaryFileStateManager.hpp"
#include "core/format/IFormat.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "core/payload/IPayload.hpp"
#include "core/payload/processor/PayloadProcessor.hpp"
#include "shared/types/defines.hpp"
#include <memory>

class CNasmPayloadProcessor : public IPayloadProcessor
{
    const CBinaryFileStateManager* m_fileManager;
    bool isImmediateValue(const std::string& value) const;
    bool isStructData(const Data_t& data) const;
    bool hasDependency(const Data_t& data) const;
    std::vector<std::string> extractPartsOfData(const Data_t& data) const;
    std::string dataLabel(const Data_t& data) const;
    data_id dataId(const IPayload* payload, const std::string sectionName, const std::string& dataLabel) const;
    bool isValidTypeName(const std::string& str) const;
    byte_vec produceDataBytes(format_ptr format, const Data_t& data) const;
public:
    CNasmPayloadProcessor(CBinaryFileStateManager* fileManager);
    const std::shared_ptr<IModificationCommand> next(const file_id& fileId, const IPayload* payload) const;
};
