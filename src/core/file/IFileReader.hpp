#pragma once
#include <string>
#include "Binary.hpp"

class IFileReader
{
public:
	virtual ~IFileReader() {};
	virtual const CBinary read(const std::string& filePath) = 0;
};
