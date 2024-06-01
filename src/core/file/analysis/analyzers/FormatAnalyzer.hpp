#pragma once

#include "../IAnalyzer.hpp"

class CFormatAnalyzer : public IAnalyzer
{
public:
	void analyze(const CBinary* binaryFile, BinaryAttributes_t& attributes);
};

