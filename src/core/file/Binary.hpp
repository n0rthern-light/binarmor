#pragma once
#include <vector>
#include <string>
#include "BinaryPointer.hpp"

#ifndef byteVector_t
typedef size_t binary_offset;
typedef const unsigned char* byte_ptr;
typedef std::vector<unsigned char> byte_vec;
#endif

class CBinary
{
	const byte_vec _bytes;
    byte_ptr at(const binary_offset& offset) const;
public:
	CBinary(const byte_vec& bytes);
	CBinary part(const binary_offset& offset = 0, const binary_offset& count = 0) const;
	byte_vec bytes() const;
    std::string string(const binary_offset& offset = 0) const;
	size_t size() const;
	CBinaryPointer pointer(const binary_offset& offset) const;

    bool operator==(const CBinary& other) const;
};
 
