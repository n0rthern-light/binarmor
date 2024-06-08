#include "PeImport.hpp"
#include <shared/value/AddressType.hpp>
#include <shared/self_obfuscation/strenc.hpp>

CPeImport::CPeImport(
    const std::string& name,
    const uint_16& hint,
    const uint_32& ordinal,
    const uint_32& rvaOriginalThunk,
    const uint_32& rvaThunk,
    const uint_32& rvaOriginalThunkAddressOfData,
    const uint_32& rvaThunkAddressOfData,
    const uint_32& sizeOfThunk
):  _name(name),
    _hint(hint),
    _ordinal(ordinal),
    _rvaOriginalThunk(rvaOriginalThunk),
    _rvaThunk(rvaThunk),
    _rvaOriginalThunkAddressOfData(rvaOriginalThunkAddressOfData),
    _rvaThunkAddressOfData(rvaThunkAddressOfData),
    _sizeOfThunk(sizeOfThunk)
{}

std::string CPeImport::name() {
    return _name;
}

uint_16 CPeImport::hint() {
    return _hint;
}

uint_32 CPeImport::ordinal() {
    return _ordinal;
}

uint_32 CPeImport::rvaOriginalThunk() {
    return _rvaOriginalThunk;
}

uint_32 CPeImport::rvaThunk() {
    return _rvaThunk;
}

uint_32 CPeImport::rvaOriginalThunkAddressOfData() {
    return _rvaOriginalThunkAddressOfData;
}

uint_32 CPeImport::rvaThunkAddressOfData() {
    return _rvaThunkAddressOfData;
}

uint_32 CPeImport::sizeOfThunk() {
    return _sizeOfThunk;
}

