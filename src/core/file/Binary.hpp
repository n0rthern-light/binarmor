#pragma once
#include <vector>
#include <string>
#include "BinaryPointer.hpp"

class CBinary
{
	const std::vector<unsigned char> bytes;
public:
	CBinary(const std::vector<unsigned char> _bytes);
	CBinary getPart(size_t offset = 0, size_t count = 0) const;
	std::vector<unsigned char> getBytes(size_t offset = 0, size_t count = 0) const;
	std::string getBytesAsString(size_t offset = 0, size_t count = 0) const;
	size_t getSize() const;
	CBinaryPointer getPointer(size_t offset) const;
};
 
