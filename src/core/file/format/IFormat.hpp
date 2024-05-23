#pragma once

#include "../attributes.hpp"
#include <shared/value/AddressValue.hpp>

class IFormat
{
public:
	virtual ~IFormat() { };
	virtual Architecture architecture() const = 0;
	virtual Type type() const = 0;
	virtual Endianness endianness() const = 0;
	virtual AddressType addressType() const = 0;
	virtual CAddressValue entryPoint() const = 0;
};

