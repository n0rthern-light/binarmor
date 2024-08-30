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
):  m_name(name),
    m_hint(hint),
    m_ordinal(ordinal),
    m_rvaOriginalThunk(rvaOriginalThunk),
    m_rvaThunk(rvaThunk),
    m_rvaOriginalThunkAddressOfData(rvaOriginalThunkAddressOfData),
    m_rvaThunkAddressOfData(rvaThunkAddressOfData),
    m_sizeOfThunk(sizeOfThunk)
{}

std::string CPeImport::name() const {
    return m_name;
}

uint_16 CPeImport::hint() const {
    return m_hint;
}

uint_32 CPeImport::ordinal() const {
    return m_ordinal;
}

uint_32 CPeImport::rvaOriginalThunk() const {
    return m_rvaOriginalThunk;
}

uint_32 CPeImport::rvaThunk() const {
    return m_rvaThunk;
}

uint_32 CPeImport::rvaOriginalThunkAddressOfData() const {
    return m_rvaOriginalThunkAddressOfData;
}

uint_32 CPeImport::rvaThunkAddressOfData() const {
    return m_rvaThunkAddressOfData;
}

uint_32 CPeImport::sizeOfThunk() const {
    return m_sizeOfThunk;
}

