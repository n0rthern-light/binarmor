#pragma once

#include "../BinaryFile.hpp"
#include "../BinaryAttributes.hpp"

class IAnalyzer
{
public:
	virtual ~IAnalyzer() {}
	virtual void analyze(CBinaryFile* binaryFile, BinaryAttributes_t& attributes) = 0;
};
