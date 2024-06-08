#ifndef SRC_CORE_FILE_ANALYSIS_ANALYZERS__FORMAT_ANALYZER_HPP_
#define SRC_CORE_FILE_ANALYSIS_ANALYZERS__FORMAT_ANALYZER_HPP_





#include "../IAnalyzer.hpp"

class CFormatAnalyzer : public IAnalyzer
{
public:
	void analyze(const CBinary* binaryFile, BinaryAttributes_t& attributes);
};




#endif // SRC_CORE_FILE_ANALYSIS_ANALYZERS__FORMAT_ANALYZER_HPP_
