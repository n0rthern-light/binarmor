#include "PeImport.hpp"
#include "core/format/IImport.hpp"
#include <shared/value/AddressType.hpp>
#include <shared/self_obfuscation/strenc.hpp>

using namespace program::core::format;
using namespace program::core::format::pe;
using namespace program::shared::types;

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

definitions_t CPeImport::definitions() const
{
    auto defs = definitions_t {
        ImportDefinition_t { rvaOriginalThunk(), sizeOfThunk() },
        ImportDefinition_t { rvaThunk(), sizeOfThunk() },
    };

    if (name() != strenc("Ordinal")) {
        const auto importByNameSize = 2 + name().length() + 1; // uint_16 hint + ascii zero terminated string
        const auto importByNames = definitions_t {
            ImportDefinition_t { rvaOriginalThunkAddressOfData(), importByNameSize },
            ImportDefinition_t { rvaThunkAddressOfData(), importByNameSize }
        };

        defs.insert(defs.end(), importByNames.begin(), importByNames.end());
    }

    return defs;
}

