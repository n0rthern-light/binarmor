#pragma once

#include "../ISection.hpp"
#include "defines.hpp"
#include <string>
#include <memory>

class CPeSection;

typedef std::shared_ptr<CPeSection> pe_section_ptr;
typedef std::vector<pe_section_ptr> pe_section_vec;

class CPeSection : public ISection
{
	std::string _name;
	CUnsigned _rawAddress;
	uint_32 _rawSize;
	CUnsigned _virtualAddress;
	uint_32 _virtualSize;
	CUnsigned _pointerToRelocations;
	uint_16 _numberOfLinenumbers;
	uint_16 _numberOfRelocations;
	uint_32 _characteristics;
public:
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

	CPeSection(const IMAGE_SECTION_HEADER& header);

	std::string name() const;
	CUnsigned baseAddress() const;
	size_t size() const;

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

