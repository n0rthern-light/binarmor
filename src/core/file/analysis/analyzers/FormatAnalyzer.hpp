#pragma once
#include "../IAnalyzer.hpp"
#include <shared/event/IEventBus.hpp>

class CFormatAnalyzer : public IAnalyzer
{
	IEventBus* eventBus;

public:
	CFormatAnalyzer(IEventBus* _eventBus);
	void analyze(CBinaryFile* binaryFile, AnalysisResult_t& result);
};
