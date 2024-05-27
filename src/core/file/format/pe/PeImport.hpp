#pragma once

#include <string>
#include "../IImport.hpp"
#include <memory>
#include <shared/types/defines.hpp>

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
};

