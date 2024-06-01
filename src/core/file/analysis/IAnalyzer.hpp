#pragma once

#include "../BinaryAttributes.hpp"
#include "core/Binary.hpp"

class IAnalyzer
{
public:
	virtual ~IAnalyzer() {}
	virtual void analyze(const CBinary* binary, BinaryAttributes_t& attributes) = 0;
};
