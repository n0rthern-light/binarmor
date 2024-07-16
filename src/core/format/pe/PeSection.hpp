#ifndef CORE_FORMAT_PE__PE_SECTION_HPP_
#define CORE_FORMAT_PE__PE_SECTION_HPP_

#include "../ISection.hpp"
#include "core/shared/BinaryPointer.hpp"
#include "defines.hpp"
#include <optional>
#include <string>
#include <memory>

class CPeSection;

typedef std::shared_ptr<CPeSection> pe_section_ptr;
typedef std::vector<pe_section_ptr> pe_section_vec;

class CPeSection : public ISection
{
    std::string m_name;
    std::optional<CBinaryPointer> m_origin;
    CUnsigned m_rawAddress;
    uint_32 m_rawSize;
    CUnsigned m_virtualAddress;
    uint_32 m_virtualSize;
    CUnsigned m_pointerToRelocations;
    uint_16 m_numberOfLinenumbers;
    uint_16 m_numberOfRelocations;
    uint_32 m_characteristics;
public:
    CPeSection(
        const std::string& name,
        const CBinaryPointer& origin,
        const CUnsigned& rawAddress,
        const uint_32& rawSize,
        const CUnsigned& virtualAddress,
        const uint_32& virtualSize,
        const CUnsigned& pointerToRelocations,
        const uint_16& numberOfLinenumbers,
        const uint_16& numberOfRelocations,
        const uint_32& characteristics
    );

    CPeSection(
        const std::string& name,
        const CUnsigned& rawAddress,
        const uint_32& rawSize,
        const CUnsigned& virtualAddress,
        const uint_32& virtualSize,
        const CUnsigned& pointerToRelocations,
        const uint_16& numberOfLinenumbers,
        const uint_16& numberOfRelocations,
        const uint_32& characteristics
    );

    CPeSection(const CBinaryPointer& origin, const IMAGE_SECTION_HEADER& header);

    std::string name() const;
    CUnsigned baseAddress() const;
    size_t size() const;
    CBinaryPointer origin() const;

    CUnsigned rawAddress() const;
    uint_32 rawSize() const;
    CUnsigned virtualAddress() const;
    uint_32 virtualSize() const;
    CUnsigned pointerToRelocations() const;
    uint_16 numberOfLinenumbers() const;
    uint_16 numberOfRelocations() const;
    uint_32 characteristics() const;

    bool operator==(const CPeSection& other) const;
};

#endif // CORE_FORMAT_PE__PE_SECTION_HPP_
