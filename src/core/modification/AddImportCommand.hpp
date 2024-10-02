#pragma once

#include "core/modification/ModificationCommand.hpp"
#include <format>

class CAddImportCommand : public IModificationCommand
{
    const file_id m_fileId;
    const std::string m_moduleName;
    const std::string m_functionName;

public:
    CAddImportCommand(
        const file_id& fileId,
        const std::string& moduleName,
        const std::string& functionName
    ):
        m_fileId(fileId),
        m_moduleName(moduleName),
        m_functionName(functionName)
    { }
    file_id fileId() const { return m_fileId; }
    CUuid modificationId() const { return { std::format("import:{}:{}", m_moduleName, m_functionName) }; }
    BinaryModificationType type() const { return BinaryModificationType::WRITE_IMPORT; }
    std::string moduleName() const { return m_moduleName; }
    std::string functionName() const { return m_functionName; }
};

