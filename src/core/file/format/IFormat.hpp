#pragma once

#include "../attributes.hpp"

class IFormat
{
public:
	virtual ~IFormat() { };
	virtual Architecture getArchitecture() const = 0;
	virtual Type getType() const = 0;
};
