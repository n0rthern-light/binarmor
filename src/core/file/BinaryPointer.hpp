#pragma once

#include <shared/types/defines.hpp>

class CBinaryPointer
{
	binary_offset _offsetInBinary;
	uint_auto _loadedAtAddress;
public:
	CBinaryPointer(binary_offset offsetInBinary, uint_auto loadedAtAddress);
	binary_offset offset();
	uint_auto ptr();
    CBinaryPointer shift(int _offset);
};

