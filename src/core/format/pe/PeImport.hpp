#ifndef CORE_FORMAT_PE__PE_IMPORT_HPP_
#define CORE_FORMAT_PE__PE_IMPORT_HPP_

#include <string>
#include "../IImport.hpp"
#include <memory>
#include <shared/types/defines.hpp>

namespace program::core::format::pe {
    class CPeImport;

    typedef std::shared_ptr<CPeImport> pe_import_ptr;
    typedef std::vector<pe_import_ptr> pe_import_vec;

    class CPeImport : public IImport
    {
        std::string m_name;
        uint_16 m_hint;
        uint_32 m_ordinal;
        uint_32 m_rvaOriginalThunk;
        uint_32 m_rvaThunk;
        uint_32 m_rvaOriginalThunkAddressOfData;
        uint_32 m_rvaThunkAddressOfData;
        uint_32 m_sizeOfThunk;
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
        std::string name() const;
        uint_16 hint() const;
        uint_32 ordinal() const;
        uint_32 rvaOriginalThunk() const;
        uint_32 rvaThunk() const;
        uint_32 rvaOriginalThunkAddressOfData() const;
        uint_32 rvaThunkAddressOfData() const;
        uint_32 sizeOfThunk() const;
        definitions_t definitions() const;
    };
}

#endif // CORE_FORMAT_PE__PE_IMPORT_HPP_
