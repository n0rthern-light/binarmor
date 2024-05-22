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
	AddressType bitType() const;
	uint32_t get32() const;
	uint64_t get64() const;
	std::uintptr_t get() const;
    std::string asDecimalString() const;
    std::string asShortHexString() const;
    std::string asFullHexString() const;
	bool operator==(const CAddressValue& other) const;
};

