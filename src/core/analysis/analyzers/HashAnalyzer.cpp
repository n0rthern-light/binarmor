#include "HashAnalyzer.hpp"

CHashAnalyzer::CHashAnalyzer(const IHasher* hasher): m_hasher(hasher) { }

void CHashAnalyzer::analyze(const CBinary& binary, BinaryFileAttributes_t& attributes)
{
    attributes.hash = binary.hash(m_hasher);
}

