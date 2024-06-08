#ifndef CORE_FORMAT_PE__PE_MODULE_HPP_
#define CORE_FORMAT_PE__PE_MODULE_HPP_

#include "../IModule.hpp"
#include <shared/types/defines.hpp>
#include "PeImport.hpp"
#include <map>

class CPeModule;

typedef std::shared_ptr<CPeModule> pe_module_ptr;
typedef std::map<std::string, pe_module_ptr> pe_module_map;

class CPeModule : public IModule
{
    std::string _name;
    uint_32 _rvaImportDescriptor;
    uint_32 _sizeOfImportDescriptor;
    pe_import_vec _imports;

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
    pe_import_vec imports() const;
};

#endif // CORE_FORMAT_PE__PE_MODULE_HPP_
