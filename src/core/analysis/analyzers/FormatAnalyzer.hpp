#ifndef CORE_ANALYSIS_ANALYZERS__FORMAT_ANALYZER_HPP_
#define CORE_ANALYSIS_ANALYZERS__FORMAT_ANALYZER_HPP_

#include "../IAnalyzer.hpp"

namespace program::core::analysis::analyzers {
    class CFormatAnalyzer : public IAnalyzer
    {
    public:
        void analyze(const program::core::shared::CBinary& binaryFile, program::core::file::BinaryFileAttributes_t& attributes);
    };
}

#endif // CORE_ANALYSIS_ANALYZERS__FORMAT_ANALYZER_HPP_
