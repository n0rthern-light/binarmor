#pragma once

#include "../ISection.hpp"
#include "../../Binary.hpp"
#include "defines.hpp"
#include <string>

class CPeSection : public ISection
{
	std::string name;
	CAddressValue rawAddress;
	uint32_t rawSize;
	CAddressValue virtualAddress;
	uint32_t virtualSize;
	CAddressValue pointerToRelocations;
	uint16_t numberOfLinenumbers;
	uint16_t numberOfRelocations;
	uint32_t characteristics;
public:
	CPeSection(
		const std::string& _name,
		const CAddressValue& _rawAddress,
		const uint32_t& _rawSize,
		const CAddressValue& _virtualAddress,
		const uint32_t& _virtualSize,
		const CAddressValue& _pointerToRelocations,
		const uint16_t& _numberOfLinenumbers,
		const uint16_t& _numberOfRelocations,
		const uint32_t& _characteristics
	);

	CPeSection(const IMAGE_SECTION_HEADER& header);

	std::string getName() const;
	CAddressValue getBaseAddress() const;
	size_t getSize() const;

	CAddressValue getRawAddress() const;
	uint32_t getRawSize() const;
	CAddressValue getVirtualAddress() const;
	uint32_t getVirtualSize() const;
	CAddressValue getPointerToRelocations() const;
	uint16_t getNumberOfLinenumbers() const;
	uint16_t getNumberOfRelocations() const;
	uint32_t getCharacteristics() const;
};

