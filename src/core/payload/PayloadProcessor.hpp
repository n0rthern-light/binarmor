#pragma once

#include "core/file/BinaryFile.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "IPayload.hpp"
#include <memory>

namespace program::core::payload
{
    class IPayloadProcessor
    {
    public:
        virtual const std::shared_ptr<modification::IModificationCommand> next(const file::file_id& fileId, const IPayload* payload) const = 0;
        virtual ~IPayloadProcessor() { };
    };
}
