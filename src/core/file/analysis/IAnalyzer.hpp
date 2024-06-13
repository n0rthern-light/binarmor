#ifndef CORE_FILE_ANALYSIS__I_ANALYZER_HPP_
#define CORE_FILE_ANALYSIS__I_ANALYZER_HPP_

#include "../BinaryAttributes.hpp"
#include "core/Binary.hpp"

class IAnalyzer
{
public:
    virtual ~IAnalyzer() {}
    virtual void analyze(const CBinary* binary, BinaryAttributes_t& attributes) = 0;
};

#endif // CORE_FILE_ANALYSIS__I_ANALYZER_HPP_
