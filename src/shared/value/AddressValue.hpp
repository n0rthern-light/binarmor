#pragma once
#include "AddressType.hpp"
#include <cstdint>
#include <string>

#ifndef as32
#define as32(t) static_cast<uint32_t>(t)
#endif

#ifndef as64
#define as64(t) static_cast<uint64_t>(t)
#endif

class CAddressValue
{
	union {
		uint32_t _32;
		uint64_t _64;
	} address;
    AddressType type;

public:
	CAddressValue(int _address);
	CAddressValue(uint32_t _address);
    CAddressValue(uint64_t _address);
	AddressType getType() const;
	uint32_t getAddress32() const;
	uint64_t getAddress64() const;
	std::uintptr_t getAddress() const;
    std::string getAddressAsDecimalString() const;
    std::string getAddressAsShortHexString() const;
    std::string getAddressAsFullHexString() const;
	bool operator==(const CAddressValue& other) const;
};

