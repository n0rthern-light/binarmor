#pragma once

#include "../IAnalyzer.hpp"

class CHashAnalyzer : public IAnalyzer
{
    const IHasher* m_hasher;
public:
    CHashAnalyzer(const IHasher* hasher);
	void analyze(CBinaryFile* binaryFile, BinaryAttributes_t& attributes);
};

