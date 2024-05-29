#pragma once

#include "AddressType.hpp"
#include "../types/defines.hpp"
#include <string>

class CAddressValue
{
	union {
		uint_32 _32;
		uint_64 _64;
	} address;
    AddressType type;

public:
	CAddressValue(int _address);
	CAddressValue(uint_32 _address);
    CAddressValue(uint_64 _address);
	AddressType bitType() const;
	uint_32 get32() const;
	uint_64 get64() const;
	uint_auto get() const;
    std::string asDecimalString() const;
    std::string asShortHexString() const;
    std::string asFullHexString() const;
	bool operator==(const CAddressValue& other) const;
};

