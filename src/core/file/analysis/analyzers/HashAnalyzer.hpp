#ifndef CORE_FILE_ANALYSIS_ANALYZERS__HASH_ANALYZER_HPP_
#define CORE_FILE_ANALYSIS_ANALYZERS__HASH_ANALYZER_HPP_

#include "../IAnalyzer.hpp"

class CHashAnalyzer : public IAnalyzer
{
    const IHasher* m_hasher;
public:
    CHashAnalyzer(const IHasher* hasher);
	void analyze(const CBinary* binary, BinaryAttributes_t& attributes);
};

#endif // CORE_FILE_ANALYSIS_ANALYZERS__HASH_ANALYZER_HPP_
