#ifndef CORE_ANALYSIS_ANALYZERS__PE_ANALYZER_HPP_
#define CORE_ANALYSIS_ANALYZERS__PE_ANALYZER_HPP_

#include "../IAnalyzer.hpp"

class CPeAnalyzer : public IAnalyzer
{
public:
    void analyze(const CBinary& binary, BinaryFileAttributes_t& attributes);
};

#endif // CORE_ANALYSIS_ANALYZERS__PE_ANALYZER_HPP_
