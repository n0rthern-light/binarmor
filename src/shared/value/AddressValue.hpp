#pragma once
#include "AddressType.hpp"
#include <cstdint>
#include <stdexcept>
#include <iostream>

class CAddressValue
{
	union {
		uint32_t _32;
		uint64_t _64;
	} address;
    AddressType type;

public:
	CAddressValue(uint32_t _address);
    CAddressValue(uint64_t _address);
	AddressType getType() const;
	uint32_t getAddress32() const;
	uint64_t getAddress64() const;
	std::uintptr_t getAddress() const;
};

