#ifndef SRC_CORE_FORMAT__I_FORMAT_HPP_
#define SRC_CORE_FORMAT__I_FORMAT_HPP_





#include "../attributes.hpp"
#include <shared/value/Unsigned.hpp>

class IFormat
{
public:
	virtual ~IFormat() { };
	virtual Architecture architecture() const = 0;
	virtual Type type() const = 0;
	virtual Endianness endianness() const = 0;
	virtual AddressType addressType() const = 0;
	virtual CUnsigned entryPoint() const = 0;
};




#endif // SRC_CORE_FORMAT__I_FORMAT_HPP_
