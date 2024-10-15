#ifndef CORE_ANALYSIS_ANALYZERS__HASH_ANALYZER_HPP_
#define CORE_ANALYSIS_ANALYZERS__HASH_ANALYZER_HPP_

#include "../IAnalyzer.hpp"

class CHashAnalyzer : public IAnalyzer
{
    const IHasher* m_hasher;
public:
    CHashAnalyzer(const IHasher* hasher);
    void analyze(const CBinary& binary, program::core::file::BinaryFileAttributes_t& attributes);
};

#endif // CORE_ANALYSIS_ANALYZERS__HASH_ANALYZER_HPP_
