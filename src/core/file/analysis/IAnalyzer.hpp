#pragma once

#include "../BinaryFile.hpp"
#include "AnalysisResult.hpp"

class IAnalyzer
{
public:
	virtual ~IAnalyzer() {}
	virtual void analyze(CBinaryFile* binaryFile, AnalysisResult_t& result) = 0;
};
