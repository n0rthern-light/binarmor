#include "AddressValue.hpp"
#include <cstdint>

CAddressValue::CAddressValue(int _address) : type(AddressType::_32_BIT) {
	address._32 = static_cast<uint32_t>(_address);
}

CAddressValue::CAddressValue(uint32_t _address) : type(AddressType::_32_BIT) {
	address._32 = _address;
}

CAddressValue::CAddressValue(uint64_t _address) : type(AddressType::_32_BIT) {
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

bool CAddressValue::operator==(const CAddressValue& other) const
{
	return getAddress() == other.getAddress();
}

