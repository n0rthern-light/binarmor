#ifndef CORE_ANALYSIS_ANALYZERS__HASH_ANALYZER_HPP_
#define CORE_ANALYSIS_ANALYZERS__HASH_ANALYZER_HPP_

#include "../IAnalyzer.hpp"

namespace program::core::analysis::analyzers {
    class CHashAnalyzer : public IAnalyzer
    {
        const program::shared::crypto::IHasher* m_hasher;
    public:
        CHashAnalyzer(const program::shared::crypto::IHasher* hasher);
        void analyze(const program::core::shared::CBinary& binary, program::core::file::BinaryFileAttributes_t& attributes);
    };
}

#endif // CORE_ANALYSIS_ANALYZERS__HASH_ANALYZER_HPP_
