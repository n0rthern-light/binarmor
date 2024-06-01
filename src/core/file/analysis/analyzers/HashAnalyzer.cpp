#include "HashAnalyzer.hpp"

CHashAnalyzer::CHashAnalyzer(const IHasher* hasher): m_hasher(hasher) { }

void CHashAnalyzer::analyze(CBinaryFile* binaryFile, BinaryAttributes_t& attributes)
{
    attributes.hash = binaryFile->binary().hash(m_hasher);
}

