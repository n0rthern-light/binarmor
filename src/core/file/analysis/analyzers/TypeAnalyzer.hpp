#pragma once

#include "BaseAnalyzer.hpp"

class CTypeAnalyzer: public BaseAnalyzer
{
public:
	using BaseAnalyzer::BaseAnalyzer;
	void analyze(CBinaryFile* binaryFile, BinaryAttributes_t& attributes);
};
