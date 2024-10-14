#pragma once

#include "core/file/BinaryFile.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "core/payload/IPayload.hpp"
#include <memory>

class IPayloadProcessor
{
public:
    virtual const std::shared_ptr<program::core::modification::IModificationCommand> next(const file_id& fileId, const IPayload* payload) const = 0;
    virtual ~IPayloadProcessor() { };
};
