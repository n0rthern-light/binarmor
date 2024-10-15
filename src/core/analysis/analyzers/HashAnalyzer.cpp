#include "HashAnalyzer.hpp"

using namespace program::core::analysis::analyzers;
using namespace program::core::file;
using namespace program::core::shared;

CHashAnalyzer::CHashAnalyzer(const IHasher* hasher): m_hasher(hasher) { }

void CHashAnalyzer::analyze(const CBinary& binary, BinaryFileAttributes_t& attributes)
{
    attributes.hash = binary.hash(m_hasher);
}

