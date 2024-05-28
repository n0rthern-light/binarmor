#pragma once

#include "../IModule.hpp"
#include "../../BinaryPointer.hpp"
#include <shared/types/defines.hpp>
#include "PeImport.hpp"
#include <map>

class CPeModule;

typedef std::shared_ptr<CPeModule> pe_module_ptr;
typedef std::map<std::string, pe_module_ptr> pe_module_map;

class CPeModule : public IModule
{
    std::string _name;
    uint_32 _rva;
    uint_32 _size;
    CBinaryPointer _origin;
    pe_import_vec _imports;

public:
    CPeModule(
        const std::string& name,
        const uint_32& rva,
        const uint_32& size,
        const CBinaryPointer& origin,
        const pe_import_vec& imports
    );
    std::string name() const;
    uint_32 rva() const;
    uint_32 size() const;
    CBinaryPointer origin() const;
    pe_import_vec imports() const;
};

