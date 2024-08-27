#ifndef CORE_FORMAT_PE__PE_MODULE_HPP_
#define CORE_FORMAT_PE__PE_MODULE_HPP_

#include "../IModule.hpp"
#include <shared/types/defines.hpp>
#include "PeImport.hpp"
#include "core/format/IImport.hpp"
#include <map>

class CPeModule;

typedef std::shared_ptr<CPeModule> pe_module_ptr;
typedef std::map<std::string, pe_module_ptr> pe_module_map;

class CPeModule : public IModule
{
    std::string m_name;
    uint_32 m_rvaImportDescriptor;
    uint_32 m_sizeOfImportDescriptor;
    pe_import_vec m_imports;

public:
    CPeModule(
        const std::string& name,
        const uint_32& rvaImportDescriptor,
        const uint_32& sizeOfImportDescriptor,
        const pe_import_vec& imports
    );
    std::string name() const;
    uint_32 rvaImportDescriptor() const;
    uint_32 sizeOfImportDescriptor() const;
    import_vec imports() const;
    pe_import_vec peImports() const;
};

#endif // CORE_FORMAT_PE__PE_MODULE_HPP_
