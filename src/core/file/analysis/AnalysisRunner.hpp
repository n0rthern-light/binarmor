#pragma once

#include <map>
#include <vector>
#include "../BinaryFile.hpp"
#include "IAnalyzer.hpp"
#include "core/attributes.hpp"
#include <shared/message/IMessageBus.hpp>
#include <memory>

typedef std::vector<std::shared_ptr<IAnalyzer>> analyzer_vec;
typedef std::map<Format, analyzer_vec> analyzer_vec_map;

class CAnalysisRunner
{
	IMessageBus* m_eventBus;
    const IHasher* m_hasher;
	analyzer_vec_map m_analyzers;
public:
	CAnalysisRunner(IMessageBus* t_eventBus, const IHasher* t_hasher);
	void run(CBinaryFile* binaryFile);
};
