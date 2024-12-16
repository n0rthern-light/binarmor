#pragma once

#include "core/file/BinaryFile.hpp"
#include "core/file/BinaryModification.hpp"
#include "shared/message/IMessage.hpp"
#include "shared/value/Uuid.hpp"

namespace program::core::modification {
    class IModificationCommand : public program::shared::message::IMessage
    {
    public:
        virtual ~IModificationCommand() { };
        virtual file::file_id fileId() const = 0;
        virtual program::shared::value::CUuid modificationId() const = 0;
        virtual file::BinaryModificationType type() const = 0;
    };
}
