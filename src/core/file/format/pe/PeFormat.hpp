#pragma once

#include "../IFormat.hpp"
#include "../../Binary.hpp"
#include "defines.hpp"

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
};

