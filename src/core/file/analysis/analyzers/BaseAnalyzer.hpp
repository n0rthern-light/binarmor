#pragma once

#include "../IAnalyzer.hpp"
#include <shared/message/IMessageBus.hpp>

class BaseAnalyzer: public IAnalyzer
{
protected:
	IMessageBus* eventBus;
public:
	BaseAnalyzer(IMessageBus* _eventBus);
	virtual void analyze(CBinaryFile* binaryFile, BinaryAttributes_t& attributes) = 0;
};

