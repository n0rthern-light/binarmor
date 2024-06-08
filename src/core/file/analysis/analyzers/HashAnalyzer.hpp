#ifndef SRC_CORE_FILE_ANALYSIS_ANALYZERS__HASH_ANALYZER_HPP_
#define SRC_CORE_FILE_ANALYSIS_ANALYZERS__HASH_ANALYZER_HPP_





#include "../IAnalyzer.hpp"

class CHashAnalyzer : public IAnalyzer
{
    const IHasher* m_hasher;
public:
    CHashAnalyzer(const IHasher* hasher);
	void analyze(const CBinary* binary, BinaryAttributes_t& attributes);
};




#endif // SRC_CORE_FILE_ANALYSIS_ANALYZERS__HASH_ANALYZER_HPP_
