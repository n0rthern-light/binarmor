#pragma once
#include <vector>

class CBinary
{
	const std::vector<unsigned char> bytes;
public:
	CBinary(const std::vector<unsigned char>& _bytes);
	const std::vector<unsigned char>& getBytes() const;
};
