#pragma once

#include "../attributes.hpp"
#include "ISection.hpp"
#include <shared/value/AddressValue.hpp>
#include <cstdint>

class IFormat
{
public:
	virtual ~IFormat() { };
	virtual Architecture getArchitecture() const = 0;
	virtual Type getType() const = 0;
	virtual Endianness getEndianness() const = 0;
	virtual AddressType getAddressType() const = 0;
	virtual CAddressValue getEntryPoint() const = 0;
};

