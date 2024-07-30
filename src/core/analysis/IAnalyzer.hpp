#ifndef CORE_ANALYSIS__I_ANALYZER_HPP_
#define CORE_ANALYSIS__I_ANALYZER_HPP_

#include "../file/BinaryAttributes.hpp"
#include "core/shared/Binary.hpp"

class IAnalyzer
{
public:
    virtual ~IAnalyzer() {}
    virtual void analyze(const CBinary& binary, BinaryAttributes_t& attributes) = 0;
};

#endif // CORE_ANALYSIS__I_ANALYZER_HPP_
