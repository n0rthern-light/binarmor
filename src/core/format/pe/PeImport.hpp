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
        program::shared::types::uint_16 m_hint;
        program::shared::types::uint_32 m_ordinal;
        program::shared::types::uint_32 m_rvaOriginalThunk;
        program::shared::types::uint_32 m_rvaThunk;
        program::shared::types::uint_32 m_rvaOriginalThunkAddressOfData;
        program::shared::types::uint_32 m_rvaThunkAddressOfData;
        program::shared::types::uint_32 m_sizeOfThunk;
    public:
        CPeImport(
            const std::string& name,
            const program::shared::types::uint_16& hint,
            const program::shared::types::uint_32& ordinal,
            const program::shared::types::uint_32& rvaOriginalThunk,
            const program::shared::types::uint_32& rvaThunk,
            const program::shared::types::uint_32& rvaOriginalThunkAddressOfData,
            const program::shared::types::uint_32& rvaThunkAddressOfData,
            const program::shared::types::uint_32& sizeOfThunk
        );
        std::string name() const;
        program::shared::types::uint_16 hint() const;
        program::shared::types::uint_32 ordinal() const;
        program::shared::types::uint_32 rvaOriginalThunk() const;
        program::shared::types::uint_32 rvaThunk() const;
        program::shared::types::uint_32 rvaOriginalThunkAddressOfData() const;
        program::shared::types::uint_32 rvaThunkAddressOfData() const;
        program::shared::types::uint_32 sizeOfThunk() const;
        definitions_t definitions() const;
    };
}

#endif // CORE_FORMAT_PE__PE_IMPORT_HPP_
