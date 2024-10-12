#pragma once

#include "core/file/BinaryFile.hpp"
#include "core/file/BinaryModification.hpp"
#include "shared/message/IMessage.hpp"
#include "shared/value/Uuid.hpp"

class IModificationCommand : public IMessage
{
public:
    virtual ~IModificationCommand() { };
    virtual file_id fileId() const = 0;
    virtual CUuid modificationId() const = 0;
    virtual BinaryModificationType type() const = 0;
};
