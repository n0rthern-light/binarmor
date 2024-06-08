#ifndef SRC_CORE_FILE_ANALYSIS_ANALYZERS__PE_ANALYZER_HPP_
#define SRC_CORE_FILE_ANALYSIS_ANALYZERS__PE_ANALYZER_HPP_





#include "../IAnalyzer.hpp"

class CPeAnalyzer : public IAnalyzer
{
public:
	void analyze(const CBinary* binary, BinaryAttributes_t& attributes);
};




#endif // SRC_CORE_FILE_ANALYSIS_ANALYZERS__PE_ANALYZER_HPP_
