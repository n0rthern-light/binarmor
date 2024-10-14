#pragma once

#include "core/modification/ModificationCommand.hpp"
#include <format>
#include <string>
#include <tuple>

namespace program::core::modification::import {
    typedef std::vector<std::tuple<std::string, std::string>> import_pair_vec_t;

    class CAddImportsCommand : public IModificationCommand
    {
        const file_id m_fileId;
        const import_pair_vec_t m_imports;

    public:
        CAddImportsCommand(
            const file_id& fileId,
            const import_pair_vec_t& imports
        ):
            m_fileId(fileId),
            m_imports(imports)
        { }
        file_id fileId() const { return m_fileId; }
        CUuid modificationId() const { return { std::format(strenc("imports")) }; }
        BinaryModificationType type() const { return BinaryModificationType::WRITE_IMPORT; }
        import_pair_vec_t imports() const { return m_imports; }
    };
};

