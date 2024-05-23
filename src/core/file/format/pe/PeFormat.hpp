#pragma once

#include "../IFormat.hpp"
#include "../../Binary.hpp"
#include "PeSection.hpp"

class CPeFormat : public IFormat
{
	CBinary* binary;
public:
	CPeFormat(CBinary* _binary);
	Architecture architecture() const;
	Type type() const;
	Endianness endianness() const;
	AddressType addressType() const;
	CAddressValue entryPoint() const;
	std::vector<std::shared_ptr<CPeSection>> sections() const;
};

