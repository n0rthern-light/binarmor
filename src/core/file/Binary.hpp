#pragma once
#include <vector>
#include <string>
#include "BinaryPointer.hpp"

#ifndef byteVector_t
typedef std::vector<unsigned char> byteVector_t;
#endif

class CBinary
{
	const byteVector_t _bytes;
public:
	CBinary(const byteVector_t bytes);
	CBinary part(size_t offset = 0, size_t count = 0) const;
	byteVector_t bytes(size_t offset = 0, size_t count = 0) const;
	std::string bytesAsString(size_t offset = 0, size_t count = 0) const;
	size_t size() const;
	CBinaryPointer pointer(size_t offset) const;

    bool operator==(const CBinary& other) const;
};
 
