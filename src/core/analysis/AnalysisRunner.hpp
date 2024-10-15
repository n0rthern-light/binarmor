#ifndef CORE_ANALYSIS__ANALYSIS_RUNNER_HPP_
#define CORE_ANALYSIS__ANALYSIS_RUNNER_HPP_

#include <map>
#include <vector>
#include "IAnalyzer.hpp"
#include "core/shared/attributes.hpp"
#include "core/file/BinaryFileAttributes.hpp"
#include <shared/message/IMessageBus.hpp>
#include <memory>

namespace program::core::analysis {
    typedef std::vector<IAnalyzer*> analyzer_vec;
    typedef std::map<Format, analyzer_vec> analyzer_vec_map;

    class CAnalysisRunner
    {
        IMessageBus* m_eventBus;
        const IHasher* m_hasher;
        analyzer_vec_map m_analyzers;
    public:
        CAnalysisRunner(IMessageBus* t_eventBus, const IHasher* t_hasher);
        void run(const CBinary& binary, program::core::file::BinaryFileAttributes_t& attributes);
    };
}

#endif // CORE_ANALYSIS__ANALYSIS_RUNNER_HPP_
