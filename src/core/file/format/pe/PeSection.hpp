#pragma once

#include "../ISection.hpp"
#include "../../Binary.hpp"
#include "defines.hpp"

class CPeSection : public ISection
{
	IMAGE_SECTION_HEADER sectionHeader;
public:
	CPeSection(const IMAGE_SECTION_HEADER& _sectionHeader);
	std::string getName() const;
	CAddressValue getBaseAddress() const;
	size_t getSize() const;
};

