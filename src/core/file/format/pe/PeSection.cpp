#include "PeSection.hpp"

CPeSection::CPeSection(
    const std::string& _name,
    const CAddressValue& _rawAddress,
    const uint32_t& _rawSize,
    const CAddressValue& _virtualAddress,
    const uint32_t& _virtualSize,
    const CAddressValue& _pointerToRelocations,
    const uint16_t& _numberOfLinenumbers,
    const uint16_t& _numberOfRelocations,
    const uint32_t& _characteristics
) : name(_name),
    rawAddress(_rawAddress),
    rawSize(_rawSize),
    virtualAddress(_virtualAddress),
    virtualSize(_virtualSize),
    pointerToRelocations(_pointerToRelocations),
    numberOfLinenumbers(_numberOfLinenumbers),
    numberOfRelocations(_numberOfRelocations),
    characteristics(_characteristics) {
}

CPeSection::CPeSection(const IMAGE_SECTION_HEADER& header)
: CPeSection(
	std::string(reinterpret_cast<const char*>(header.Name)),
	CAddressValue(header.PointerToRawData),
	header.SizeOfRawData,
	CAddressValue(header.VirtualAddress),
	header.Misc.VirtualSize,
	CAddressValue(header.PointerToRelocations),
	header.NumberOfLinenumbers,
	header.NumberOfRelocations,
	header.Characteristics
) { }

std::string CPeSection::getName() const
{
	return name;
}

CAddressValue CPeSection::getBaseAddress() const
{
	return getRawAddress();
}

size_t CPeSection::getSize() const
{
	return static_cast<size_t>(getRawSize());
}

CAddressValue CPeSection::getRawAddress() const
{
	return rawAddress;
}

uint32_t CPeSection::getRawSize() const
{
	return rawSize;
}

CAddressValue CPeSection::getVirtualAddress() const
{
	return virtualAddress;
}

uint32_t CPeSection::getVirtualSize() const
{
	return virtualSize;
}

CAddressValue CPeSection::getPointerToRelocations() const
{
	return pointerToRelocations;
}

uint16_t CPeSection::getNumberOfLinenumbers() const
{
	return numberOfLinenumbers;
}

uint16_t CPeSection::getNumberOfRelocations() const
{
	return numberOfRelocations;
}

uint32_t CPeSection::getCharacteristics() const
{
	return characteristics;
}

bool CPeSection::operator==(const CPeSection& other) const
{
	if (name != other.name) {
		return false;
	}

	if (rawAddress != other.rawAddress) {
		return false;
	}

	if (rawSize != other.rawSize) {
		return false;
	}

	if (virtualAddress != other.virtualAddress) {
		return false;
	}

	if (virtualSize != other.virtualSize) {
		return false;
	}

	if (pointerToRelocations != other.pointerToRelocations) {
		return false;
	}

	if (numberOfLinenumbers != other.numberOfLinenumbers) {
		return false;
	}

	if (numberOfRelocations != other.numberOfRelocations) {
		return false;
	}

	if (characteristics != other.characteristics) {
		return false;
	}

	return true;
}

