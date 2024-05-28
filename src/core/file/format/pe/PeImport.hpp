#pragma once

#include <string>
#include "../IImport.hpp"
#include <memory>
#include <shared/types/defines.hpp>
#include "../../BinaryPointer.hpp"

class CPeImport;

typedef std::shared_ptr<CPeImport> pe_import_ptr;
typedef std::vector<pe_import_ptr> pe_import_vec;

class CPeImport : IImport
{
    std::string _name;
    uint_16 _hint;
    uint_32 _ordinal;
    uint_32 _rva;
    uint_32 _size;
    CBinaryPointer _origin;

public:
    CPeImport(
        const std::string& name,
        const uint_16& hint,
        const uint_32& ordinal,
        const uint_32& rva,
        const uint_32& size,
        const CBinaryPointer& origin
    );
};

