#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <shared/value/AddressValue.hpp>

class ISection {
public:
    virtual ~ISection() = default;

    virtual std::string getName() const = 0;
	virtual CAddressValue getBaseAddress() const = 0;
    virtual size_t getSize() const = 0;
};

