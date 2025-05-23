#ifndef CORE_ANALYSIS_ANALYZERS__FORMAT_ANALYZER_HPP_
#define CORE_ANALYSIS_ANALYZERS__FORMAT_ANALYZER_HPP_

#include "../IAnalyzer.hpp"

class CFormatAnalyzer : public IAnalyzer
{
public:
    void analyze(const CBinary& binaryFile, BinaryFileAttributes_t& attributes);
};

#endif // CORE_ANALYSIS_ANALYZERS__FORMAT_ANALYZER_HPP_
