#pragma once

#include <vector>
#include "../BinaryFile.hpp"
#include "IAnalyzer.hpp"
#include <shared/message/IMessageBus.hpp>

class CAnalysisRunner
{
	IMessageBus* eventBus;
	std::vector<IAnalyzer*> analyzers;
public:
	CAnalysisRunner(IMessageBus* _eventBus);
	void run(CBinaryFile* binaryFile);
};
