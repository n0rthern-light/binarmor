#pragma once

#include <string>
#include <shared/value/AddressValue.hpp>

class ISection {
public:
    virtual ~ISection() = default;

    virtual std::string name() const = 0;
	virtual CAddressValue baseAddress() const = 0;
    virtual size_t size() const = 0;
};

