#include "PeSection.hpp"

CPeSection::CPeSection(
    const std::string& name,
    const CUnsigned& rawAddress,
    const uint_32& rawSize,
    const CUnsigned& virtualAddress,
    const uint_32& virtualSize,
    const CUnsigned& pointerToRelocations,
    const uint_16& numberOfLinenumbers,
    const uint_16& numberOfRelocations,
    const uint_32& characteristics
) : _name(name), _rawAddress(rawAddress),
    _rawSize(rawSize),
    _virtualAddress(virtualAddress),
    _virtualSize(virtualSize),
    _pointerToRelocations(pointerToRelocations),
    _numberOfLinenumbers(numberOfLinenumbers),
    _numberOfRelocations(numberOfRelocations),
    _characteristics(characteristics) {
}

CPeSection::CPeSection(const IMAGE_SECTION_HEADER& header)
: CPeSection(
    std::string(reinterpret_cast<const char*>(header.Name)),
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
    return _name;
}

CUnsigned CPeSection::baseAddress() const
{
    return rawAddress();
}

size_t CPeSection::size() const
{
    return static_cast<size_t>(rawSize());
}

CUnsigned CPeSection::rawAddress() const
{
    return _rawAddress;
}

uint_32 CPeSection::rawSize() const
{
    return _rawSize;
}

CUnsigned CPeSection::virtualAddress() const
{
    return _virtualAddress;
}

uint_32 CPeSection::virtualSize() const
{
    return _virtualSize;
}

CUnsigned CPeSection::pointerToRelocations() const
{
    return _pointerToRelocations;
}

uint_16 CPeSection::numberOfLinenumbers() const
{
    return _numberOfLinenumbers;
}

uint_16 CPeSection::numberOfRelocations() const
{
    return _numberOfRelocations;
}

uint_32 CPeSection::characteristics() const
{
    return _characteristics;
}

bool CPeSection::operator==(const CPeSection& other) const
{
    if (_name != other._name) {
        return false;
    }

    if (_rawAddress != other._rawAddress) {
        return false;
    }

    if (_rawSize != other._rawSize) {
        return false;
    }

    if (_virtualAddress != other._virtualAddress) {
        return false;
    }

    if (_virtualSize != other._virtualSize) {
        return false;
    }

    if (_pointerToRelocations != other._pointerToRelocations) {
        return false;
    }

    if (_numberOfLinenumbers != other._numberOfLinenumbers) {
        return false;
    }

    if (_numberOfRelocations != other._numberOfRelocations) {
        return false;
    }

    if (_characteristics != other._characteristics) {
        return false;
    }

    return true;
}

