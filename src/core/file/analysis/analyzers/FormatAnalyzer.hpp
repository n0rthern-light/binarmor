#ifndef CORE_FILE_ANALYSIS_ANALYZERS__FORMAT_ANALYZER_HPP_
#define CORE_FILE_ANALYSIS_ANALYZERS__FORMAT_ANALYZER_HPP_

#include "../IAnalyzer.hpp"

class CFormatAnalyzer : public IAnalyzer
{
public:
    void analyze(const CBinary* binaryFile, BinaryAttributes_t& attributes);
};

#endif // CORE_FILE_ANALYSIS_ANALYZERS__FORMAT_ANALYZER_HPP_
