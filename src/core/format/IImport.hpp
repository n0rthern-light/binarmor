#ifndef CORE_FORMAT__I_IMPORT_HPP_
#define CORE_FORMAT__I_IMPORT_HPP_

#include "shared/types/defines.hpp"
#include <memory>
#include <vector>

namespace program::core::format {
    struct ImportDefinition_t;
    class IImport;

    typedef std::shared_ptr<IImport> import_ptr;
    typedef std::vector<import_ptr> import_vec;
    typedef std::vector<ImportDefinition_t> definitions_t;

    struct ImportDefinition_t
    {
        binary_offset rva;
        binary_offset size;
    };

    class IImport
    {
    public:
        virtual ~IImport() { };
        virtual std::string name() const = 0;
        virtual definitions_t definitions() const = 0;
    };
}

#endif // CORE_FORMAT__I_IMPORT_HPP_
