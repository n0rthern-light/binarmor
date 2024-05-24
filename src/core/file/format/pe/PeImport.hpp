#pragma once

#include <stddef.h>
#include <string>
#include "../IImport.hpp"
#include "../../Binary.hpp"
#include "shared/value/AddressType.hpp"
#include <memory>
#include <vector>

class CPeImport;

typedef std::shared_ptr<CPeImport> pe_import_ptr;
typedef std::vector<pe_import_ptr> pe_import_vec;

class CPeImport : IImport
{
    std::string _module;
    std::string _name;
    uint16_t _hint;
    uint32_t _ordinal;
public:
    CPeImport(
        const std::string& module,
        const std::string& name,
        const uint16_t& hint,
        const uint32_t& ordinal
    );
    static pe_import_vec readList(CBinary* binary, AddressType addressType);
};

