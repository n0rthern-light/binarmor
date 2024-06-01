#pragma once

#include "../IAnalyzer.hpp"

class CPeAnalyzer : public IAnalyzer
{
public:
	void analyze(const CBinary* binary, BinaryAttributes_t& attributes);
};

