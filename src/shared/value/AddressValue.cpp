#include "AddressValue.hpp"
#include "AddressType.hpp"

CAddressValue::CAddressValue(int _address) : type(AddressType::_32_BIT) {
	address._32 = as_32(_address);
}

CAddressValue::CAddressValue(uint_32 _address) : type(AddressType::_32_BIT) {
	address._32 = _address;
}

CAddressValue::CAddressValue(uint_64 _address) : type(AddressType::_64_BIT) {
	address._64 = _address;
}

AddressType CAddressValue::bitType() const
{
	return type;
}

uint_32 CAddressValue::get32() const
{
	return address._32;
}

uint_64 CAddressValue::get64() const
{
	return address._64;
}

uint_auto CAddressValue::get() const
{
	if (type == AddressType::_64_BIT) {
		return as_auto(get64());
	} else {
		return as_auto(get32());
	}
}

std::string CAddressValue::asDecimalString() const
{
   char buffer[21];

    if (type == AddressType::_32_BIT) {
        std::snprintf(buffer, sizeof(buffer), "%u", get32());
    } else {
        std::snprintf(buffer, sizeof(buffer), "%llu", get64());
    }

    return buffer;

}

std::string CAddressValue::asShortHexString() const
{
   char buffer[21];

    if (type == AddressType::_32_BIT) {
        std::snprintf(buffer, sizeof(buffer), "0x%X", get32());
    } else {
        std::snprintf(buffer, sizeof(buffer), "0x%llX", get64());
    }

    return std::string(buffer);
}

std::string CAddressValue::asFullHexString() const
{
   char buffer[21];

    if (type == AddressType::_32_BIT) {
        std::snprintf(buffer, sizeof(buffer), "0x%08X", get32());
    } else {
        std::snprintf(buffer, sizeof(buffer), "0x%016llX", get64());
    }

    return std::string(buffer);
}

bool CAddressValue::operator==(const CAddressValue& other) const
{
	return get() == other.get();
}

