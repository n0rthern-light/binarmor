#pragma once

#include "../IAnalyzer.hpp"
#include <shared/event/IEventBus.hpp>

class BaseAnalyzer: public IAnalyzer
{
protected:
	IEventBus* eventBus;
public:
	BaseAnalyzer(IEventBus* _eventBus);
	virtual void analyze(CBinaryFile* binaryFile, BinaryAttributes_t& attributes) = 0;
};
