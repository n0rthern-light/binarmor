#include "PeSection.hpp"

CPeSection::CPeSection(const IMAGE_SECTION_HEADER& _sectionHeader)
{
	sectionHeader = _sectionHeader;
}

std::string CPeSection::getName() const
{
	return std::string(reinterpret_cast<const char*>(sectionHeader.Name), 8);
}

CAddressValue CPeSection::getBaseAddress() const
{
	return CAddressValue(sectionHeader.Misc.PhysicalAddress);
}

size_t CPeSection::getSize() const
{
	return sectionHeader.Misc.VirtualSize;
}

