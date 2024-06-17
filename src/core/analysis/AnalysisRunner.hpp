#ifndef CORE_FILE_ANALYSIS__ANALYSIS_RUNNER_HPP_
#define CORE_FILE_ANALYSIS__ANALYSIS_RUNNER_HPP_

#include <map>
#include <vector>
#include "IAnalyzer.hpp"
#include "core/attributes.hpp"
#include "core/file/BinaryAttributes.hpp"
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
    void run(const CBinary* binary, BinaryAttributes_t& attributes);
};

#endif // CORE_FILE_ANALYSIS__ANALYSIS_RUNNER_HPP_
