#pragma once
#include "../IFileReader.hpp"

class CfstreamFileReader : public IFileReader
{
public:
	const CBinary read(const std::string& filePath);
};
