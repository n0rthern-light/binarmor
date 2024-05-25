#pragma once

#include <string>
#include "../IImport.hpp"
#include "../../Binary.hpp"
#include "shared/value/AddressType.hpp"
#include <memory>

class CPeImport;

typedef std::shared_ptr<CPeImport> pe_import_ptr;
typedef std::vector<pe_import_ptr> pe_import_vec;

class CPeImport : IImport
{
    std::string _module;
    std::string _name;
    uint_16 _hint;
    uint_32 _ordinal;
public:
    CPeImport(
        const std::string& module,
        const std::string& name,
        const uint_16& hint,
        const uint_32& ordinal
    );
    static pe_import_vec readList(CBinary* binary, AddressType addressType);
};

