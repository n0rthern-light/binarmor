#pragma once

#include "../IAnalyzer.hpp"

class CHashAnalyzer : public IAnalyzer
{
    const IHasher* m_hasher;
public:
    CHashAnalyzer(const IHasher* hasher);
	void analyze(const CBinary* binary, BinaryAttributes_t& attributes);
};

