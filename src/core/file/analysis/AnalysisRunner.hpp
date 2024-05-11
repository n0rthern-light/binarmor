#pragma once

#include <vector>
#include "../BinaryFile.hpp"
#include "IAnalyzer.hpp"
#include <shared/event/IEventBus.hpp>

class CAnalysisRunner
{
	IEventBus* eventBus;
	std::vector<IAnalyzer*> analyzers;
public:
	CAnalysisRunner(IEventBus* _eventBus);
	void run(CBinaryFile* binaryFile);
};
