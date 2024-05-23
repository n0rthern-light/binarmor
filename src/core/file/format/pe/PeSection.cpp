#include "PeSection.hpp"
#include "functions.hpp"

CPeSection::CPeSection(
    const std::string& name,
    const CAddressValue& rawAddress,
    const uint32_t& rawSize,
    const CAddressValue& virtualAddress,
    const uint32_t& virtualSize,
    const CAddressValue& pointerToRelocations,
    const uint16_t& numberOfLinenumbers,
    const uint16_t& numberOfRelocations,
    const uint32_t& characteristics
) : _name(name),
    _rawAddress(rawAddress),
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
	CAddressValue(header.PointerToRawData),
	header.SizeOfRawData,
	CAddressValue(header.VirtualAddress),
	header.Misc.VirtualSize,
	CAddressValue(header.PointerToRelocations),
	header.NumberOfLinenumbers,
	header.NumberOfRelocations,
	header.Characteristics
) { }

pe_section_vec CPeSection::readList(CBinary* binary, AddressType addressType)
{
	auto vec = pe_section_vec();

	auto numberOfSections = format::pe::numberOfSections(binary, addressType);
    auto offset = format::pe::sectionsStartOffset(binary, addressType);

	auto binaryPointer = binary->pointer(offset);
    for(int i = 0; i < numberOfSections; ++i)
    {
        auto sectionOrigin = binaryPointer.shift(i * sizeof(IMAGE_SECTION_HEADER));
        auto sectionHeader = *reinterpret_cast<IMAGE_SECTION_HEADER*>(sectionOrigin.ptr());
        auto section = std::make_shared<CPeSection>(sectionHeader);
        vec.push_back(section);
    }

	return vec;
}

std::string CPeSection::name() const
{
	return _name;
}

CAddressValue CPeSection::baseAddress() const
{
	return rawAddress();
}

size_t CPeSection::size() const
{
	return static_cast<size_t>(rawSize());
}

CAddressValue CPeSection::rawAddress() const
{
	return _rawAddress;
}

uint32_t CPeSection::rawSize() const
{
	return _rawSize;
}

CAddressValue CPeSection::virtualAddress() const
{
	return _virtualAddress;
}

uint32_t CPeSection::virtualSize() const
{
	return _virtualSize;
}

CAddressValue CPeSection::pointerToRelocations() const
{
	return _pointerToRelocations;
}

uint16_t CPeSection::numberOfLinenumbers() const
{
	return _numberOfLinenumbers;
}

uint16_t CPeSection::numberOfRelocations() const
{
	return _numberOfRelocations;
}

uint32_t CPeSection::characteristics() const
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

