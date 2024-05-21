#pragma once

#include "../IFormat.hpp"
#include "../../Binary.hpp"
#include "PeSection.hpp"

class CPeFormat : public IFormat
{
	CBinary* binary;
public:
	CPeFormat(CBinary* _binary);
	Architecture getArchitecture() const;
	Type getType() const;
	Endianness getEndianness() const;
	AddressType getAddressType() const;
	CAddressValue getEntryPoint() const;
	std::vector<std::shared_ptr<CPeSection>> getSections() const;
};

