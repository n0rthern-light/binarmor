#pragma once
#include "../IFileReader.hpp"

class CfstreamFileReader : public IFileReader
{
	const CBinary read(const std::string& filePath);
};
