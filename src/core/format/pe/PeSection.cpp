#include "PeSection.hpp"
#include "core/format/pe/defines.hpp"
#include "core/format/pe/functions.hpp"
#include "shared/types/defines.hpp"

using namespace program::core::format::pe;

CPeSection::CPeSection(
    const std::string& name,
    const binary_offset& headerOffset,
    const CUnsigned& rawAddress,
    const uint_32& rawSize,
    const CUnsigned& virtualAddress,
    const uint_32& virtualSize,
    const CUnsigned& pointerToRelocations,
    const uint_16& numberOfLinenumbers,
    const uint_16& numberOfRelocations,
    const uint_32& characteristics
) : m_name(name),
    m_headerOffset(headerOffset),
    m_rawAddress(rawAddress),
    m_rawSize(rawSize),
    m_virtualAddress(virtualAddress),
    m_virtualSize(virtualSize),
    m_pointerToRelocations(pointerToRelocations),
    m_numberOfLinenumbers(numberOfLinenumbers),
    m_numberOfRelocations(numberOfRelocations),
    m_characteristics(characteristics) {
}

CPeSection::CPeSection(const binary_offset& headerOffset, const IMAGE_SECTION_HEADER& header)
: CPeSection(
    std::string(reinterpret_cast<const char*>(header.Name)),
    headerOffset,
    CUnsigned(header.PointerToRawData),
    header.SizeOfRawData,
    CUnsigned(header.VirtualAddress),
    header.Misc.VirtualSize,
    CUnsigned(header.PointerToRelocations),
    header.NumberOfLinenumbers,
    header.NumberOfRelocations,
    header.Characteristics
) { }

std::string CPeSection::name() const
{
    return m_name;
}

CUnsigned CPeSection::baseAddress() const
{
    return rawAddress();
}

size_t CPeSection::size() const
{
    return static_cast<size_t>(rawSize());
}

binary_offset CPeSection::headerOffset() const
{
    return m_headerOffset;
}

CSectionPermissions CPeSection::permissions() const
{
    return format::pe::convertCharacteristicsToSectionPermissions(m_characteristics);
}

unsigned char CPeSection::nullByteRepresentation() const
{
    return PE_SECTION_NULL_BYTE;
}

CUnsigned CPeSection::rawAddress() const
{
    return m_rawAddress;
}

uint_32 CPeSection::rawSize() const
{
    return m_rawSize;
}

CUnsigned CPeSection::virtualAddress() const
{
    return m_virtualAddress;
}

uint_32 CPeSection::virtualSize() const
{
    return m_virtualSize;
}

CUnsigned CPeSection::pointerToRelocations() const
{
    return m_pointerToRelocations;
}

uint_16 CPeSection::numberOfLinenumbers() const
{
    return m_numberOfLinenumbers;
}

uint_16 CPeSection::numberOfRelocations() const
{
    return m_numberOfRelocations;
}

uint_32 CPeSection::characteristics() const
{
    return m_characteristics;
}

bool CPeSection::operator==(const CPeSection& other) const
{
    if (m_name != other.m_name) {
        return false;
    }

    if (m_rawAddress != other.m_rawAddress) {
        return false;
    }

    if (m_rawSize != other.m_rawSize) {
        return false;
    }

    if (m_virtualAddress != other.m_virtualAddress) {
        return false;
    }

    if (m_virtualSize != other.m_virtualSize) {
        return false;
    }

    if (m_pointerToRelocations != other.m_pointerToRelocations) {
        return false;
    }

    if (m_numberOfLinenumbers != other.m_numberOfLinenumbers) {
        return false;
    }

    if (m_numberOfRelocations != other.m_numberOfRelocations) {
        return false;
    }

    if (m_characteristics != other.m_characteristics) {
        return false;
    }

    return true;
}

