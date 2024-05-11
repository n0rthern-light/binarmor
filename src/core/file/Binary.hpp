#pragma once
#include <vector>
#include <string>

class CBinary
{
	const std::vector<unsigned char> bytes;
public:
	CBinary(const std::vector<unsigned char> _bytes);
	const CBinary getPart(size_t offset = 0, size_t count = 0) const;
	const std::vector<unsigned char> getBytes(size_t offset = 0, size_t count = 0) const;
	const std::string getBytesAsString(size_t offset = 0, size_t count = 0) const;
	const size_t getSize() const;
};
