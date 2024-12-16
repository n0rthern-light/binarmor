#ifndef CORE_ANALYSIS__I_ANALYZER_HPP_
#define CORE_ANALYSIS__I_ANALYZER_HPP_

#include "../file/BinaryFileAttributes.hpp"
#include "core/shared/Binary.hpp"

namespace program::core::analysis
{
    class IAnalyzer
    {
    public:
        virtual ~IAnalyzer() {}
        virtual void analyze(const program::core::shared::CBinary& binary, program::core::file::BinaryFileAttributes_t& attributes) = 0;
    };
}

#endif // CORE_ANALYSIS__I_ANALYZER_HPP_
