#ifndef CORE_FORMAT_PE__PE_SECTION_HPP_
#define CORE_FORMAT_PE__PE_SECTION_HPP_

#include "../ISection.hpp"
#include "core/shared/SectionPermissions.hpp"
#include "defines.hpp"
#include "shared/types/defines.hpp"
#include <string>
#include <memory>

namespace program::core::format::pe {
    class CPeSection;

    typedef std::shared_ptr<CPeSection> pe_section_ptr;
    typedef std::vector<pe_section_ptr> pe_section_vec;

    class CPeSection : public ISection
    {
        std::string m_name;
        program::shared::types::binary_offset m_headerOffset;
        program::shared::value::CUnsigned m_rawAddress;
        program::shared::types::uint_32 m_rawSize;
        program::shared::value::CUnsigned m_virtualAddress;
        program::shared::types::uint_32 m_virtualSize;
        program::shared::value::CUnsigned m_pointerToRelocations;
        program::shared::types::uint_16 m_numberOfLinenumbers;
        program::shared::types::uint_16 m_numberOfRelocations;
        program::shared::types::uint_32 m_characteristics;
    public:
        CPeSection(
            const std::string& name,
            const program::shared::types::binary_offset& headerOffset,
            const program::shared::value::CUnsigned& rawAddress,
            const program::shared::types::uint_32& rawSize,
            const program::shared::value::CUnsigned& virtualAddress,
            const program::shared::types::uint_32& virtualSize,
            const program::shared::value::CUnsigned& pointerToRelocations,
            const program::shared::types::uint_16& numberOfLinenumbers,
            const program::shared::types::uint_16& numberOfRelocations,
            const program::shared::types::uint_32& characteristics
        );

        CPeSection(const program::shared::types::binary_offset& headerOffset, const IMAGE_SECTION_HEADER& header);

        std::string name() const;
        program::shared::value::CUnsigned baseAddress() const;
        size_t size() const;
        program::shared::types::binary_offset headerOffset() const;
        program::core::shared::CSectionPermissions permissions() const;
        unsigned char nullByteRepresentation() const;

        program::shared::value::CUnsigned rawAddress() const;
        program::shared::types::uint_32 rawSize() const;
        program::shared::value::CUnsigned virtualAddress() const;
        program::shared::types::uint_32 virtualSize() const;
        program::shared::value::CUnsigned pointerToRelocations() const;
        program::shared::types::uint_16 numberOfLinenumbers() const;
        program::shared::types::uint_16 numberOfRelocations() const;
        program::shared::types::uint_32 characteristics() const;

        bool operator==(const CPeSection& other) const;
    };
}

#endif // CORE_FORMAT_PE__PE_SECTION_HPP_
