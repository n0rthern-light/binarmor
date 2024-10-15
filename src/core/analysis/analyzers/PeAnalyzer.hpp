#ifndef CORE_ANALYSIS_ANALYZERS__PE_ANALYZER_HPP_
#define CORE_ANALYSIS_ANALYZERS__PE_ANALYZER_HPP_

#include "../IAnalyzer.hpp"

namespace program::core::analysis::analyzers {
    class CPeAnalyzer : public IAnalyzer
    {
    public:
        void analyze(const CBinary& binary, program::core::file::BinaryFileAttributes_t& attributes);
    };
}

#endif // CORE_ANALYSIS_ANALYZERS__PE_ANALYZER_HPP_
