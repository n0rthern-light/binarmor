#pragma once

#include "core/file/BinaryFile.hpp"
#include "core/file/BinaryModification.hpp"
#include "shared/message/IMessage.hpp"
#include "shared/value/Uuid.hpp"

namespace program::core::modification {
    class IModificationCommand : public IMessage
    {
    public:
        virtual ~IModificationCommand() { };
        virtual file::file_id fileId() const = 0;
        virtual CUuid modificationId() const = 0;
        virtual file::BinaryModificationType type() const = 0;
    };
}
