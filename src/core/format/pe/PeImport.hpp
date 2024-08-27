#ifndef CORE_FORMAT_PE__PE_IMPORT_HPP_
#define CORE_FORMAT_PE__PE_IMPORT_HPP_

#include <string>
#include "../IImport.hpp"
#include <memory>
#include <shared/types/defines.hpp>

class CPeImport;

typedef std::shared_ptr<CPeImport> pe_import_ptr;
typedef std::vector<pe_import_ptr> pe_import_vec;

// todo: add address of data size

class CPeImport : public IImport
{
    std::string _name;
    uint_16 _hint;
    uint_32 _ordinal;
    uint_32 _rvaOriginalThunk;
    uint_32 _rvaThunk;
    uint_32 _rvaOriginalThunkAddressOfData;
    uint_32 _rvaThunkAddressOfData;
    uint_32 _sizeOfThunk;
public:
    CPeImport(
        const std::string& name,
        const uint_16& hint,
        const uint_32& ordinal,
        const uint_32& rvaOriginalThunk,
        const uint_32& rvaThunk,
        const uint_32& rvaOriginalThunkAddressOfData,
        const uint_32& rvaThunkAddressOfData,
        const uint_32& sizeOfThunk
    );
    std::string name();
    uint_16 hint();
    uint_32 ordinal();
    uint_32 rvaOriginalThunk();
    uint_32 rvaThunk();
    uint_32 rvaOriginalThunkAddressOfData();
    uint_32 rvaThunkAddressOfData();
    uint_32 sizeOfThunk();
};

#endif // CORE_FORMAT_PE__PE_IMPORT_HPP_
