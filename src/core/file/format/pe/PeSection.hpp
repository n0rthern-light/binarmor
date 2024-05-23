#pragma once

#include "../ISection.hpp"
#include "defines.hpp"
#include <string>

class CPeSection : public ISection
{
	std::string _name;
	CAddressValue _rawAddress;
	uint32_t _rawSize;
	CAddressValue _virtualAddress;
	uint32_t _virtualSize;
	CAddressValue _pointerToRelocations;
	uint16_t _numberOfLinenumbers;
	uint16_t _numberOfRelocations;
	uint32_t _characteristics;
public:
	CPeSection(
		const std::string& name,
		const CAddressValue& rawAddress,
		const uint32_t& rawSize,
		const CAddressValue& virtualAddress,
		const uint32_t& virtualSize,
		const CAddressValue& pointerToRelocations,
		const uint16_t& numberOfLinenumbers,
		const uint16_t& numberOfRelocations,
		const uint32_t& characteristics
	);

	CPeSection(const IMAGE_SECTION_HEADER& header);

	std::string name() const;
	CAddressValue baseAddress() const;
	size_t size() const;

	CAddressValue rawAddress() const;
	uint32_t rawSize() const;
	CAddressValue virtualAddress() const;
	uint32_t virtualSize() const;
	CAddressValue pointerToRelocations() const;
	uint16_t numberOfLinenumbers() const;
	uint16_t numberOfRelocations() const;
	uint32_t characteristics() const;

	bool operator==(const CPeSection& other) const;
};

