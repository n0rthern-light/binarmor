#pragma once

#include "../IAnalyzer.hpp"

class CPeAnalyzer : public IAnalyzer
{
public:
	void analyze(CBinaryFile* binaryFile, BinaryAttributes_t& attributes);
};

