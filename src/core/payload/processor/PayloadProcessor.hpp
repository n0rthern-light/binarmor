#pragma once

#include "core/file/BinaryFile.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "core/payload/IPayload.hpp"
#include <optional>

class IPayloadProcessor
{
public:
    virtual const std::optional<CAddBytesCommand> next(const file_id& fileId, const IPayload* payload) const = 0;
    virtual ~IPayloadProcessor() { };
};
