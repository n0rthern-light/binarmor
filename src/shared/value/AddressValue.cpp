#include "AddressValue.hpp"
#include "AddressType.hpp"
#include <cstdint>
#include <cstdio>

CAddressValue::CAddressValue(int _address) : type(AddressType::_32_BIT) {
	address._32 = static_cast<uint32_t>(_address);
}

CAddressValue::CAddressValue(uint32_t _address) : type(AddressType::_32_BIT) {
	address._32 = _address;
}

CAddressValue::CAddressValue(uint64_t _address) : type(AddressType::_64_BIT) {
	address._64 = _address;
}

AddressType CAddressValue::getType() const
{
	return type;
}

uint32_t CAddressValue::getAddress32() const
{
	return address._32;
}

uint64_t CAddressValue::getAddress64() const
{
	return address._64;
}

std::uintptr_t CAddressValue::getAddress() const
{
	if (type == AddressType::_64_BIT) {
		return static_cast<std::uintptr_t>(getAddress64());
	} else {
		return static_cast<std::uintptr_t>(getAddress32());
	}
}

std::string CAddressValue::getAddressAsDecimalString() const
{
   char buffer[21];

    if (type == AddressType::_32_BIT) {
        std::snprintf(buffer, sizeof(buffer), "%u", getAddress32());
    } else {
        std::snprintf(buffer, sizeof(buffer), "%llu", getAddress64());
    }

    return buffer;

}

std::string CAddressValue::getAddressAsShortHexString() const
{
   char buffer[21];

    if (type == AddressType::_32_BIT) {
        std::snprintf(buffer, sizeof(buffer), "0x%X", getAddress32());
    } else {
        std::snprintf(buffer, sizeof(buffer), "0x%llX", getAddress64());
    }

    return std::string(buffer);
}

std::string CAddressValue::getAddressAsFullHexString() const
{
   char buffer[21];

    if (type == AddressType::_32_BIT) {
        std::snprintf(buffer, sizeof(buffer), "0x%08X", getAddress32());
    } else {
        std::snprintf(buffer, sizeof(buffer), "0x%016llX", getAddress64());
    }

    return std::string(buffer);
}

bool CAddressValue::operator==(const CAddressValue& other) const
{
	return getAddress() == other.getAddress();
}

