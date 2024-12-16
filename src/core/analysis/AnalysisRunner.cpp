#include "AnalysisRunner.hpp"
#include "analyzers/FormatAnalyzer.hpp"
#include "analyzers/PeAnalyzer.hpp"
#include "analyzers/HashAnalyzer.hpp"
#include "../shared/attributes.hpp"
#include "core/file/BinaryFileAttributes.hpp"

using namespace program::core::analysis;
using namespace program::core::analysis::analyzers;
using namespace program::core::file;
using namespace program::core::shared;
using namespace program::shared::crypto;
using namespace program::shared::message;

CAnalysisRunner::CAnalysisRunner(IMessageBus* t_eventBus, const IHasher* t_hasher): m_eventBus(t_eventBus), m_hasher(t_hasher)
{
    m_analyzers = { };

    m_analyzers[Format::UNKNOWN] = {
        new CFormatAnalyzer(),
        new CHashAnalyzer(m_hasher)
    };

    m_analyzers[Format::Windows_PE] = {
        new CPeAnalyzer()
    };
}

void CAnalysisRunner::run(const CBinary& binary, BinaryFileAttributes_t& binaryAttributes)
{
    const auto initialFormat = binaryAttributes.format;

    for (const auto& analyzer : m_analyzers[initialFormat]) {
        analyzer->analyze(binary, binaryAttributes);
    }

    if (binaryAttributes.format != initialFormat) {
        run(binary, binaryAttributes);
    }
}

