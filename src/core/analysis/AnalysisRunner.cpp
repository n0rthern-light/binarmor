#include "AnalysisRunner.hpp"
#include "analyzers/FormatAnalyzer.hpp"
#include "analyzers/PeAnalyzer.hpp"
#include "analyzers/HashAnalyzer.hpp"
#include "../shared/attributes.hpp"
#include "core/file/BinaryAttributes.hpp"

CAnalysisRunner::CAnalysisRunner(IMessageBus* t_eventBus, const IHasher* t_hasher): m_eventBus(t_eventBus), m_hasher(t_hasher)
{
	m_analyzers = { };

    m_analyzers[Format::UNKNOWN] = {
        std::make_shared<CFormatAnalyzer>(),
        std::make_shared<CHashAnalyzer>(m_hasher)
    };

    m_analyzers[Format::Windows_PE] = {
        std::make_shared<CPeAnalyzer>()
    };
}

void CAnalysisRunner::run(const CBinary& binary, BinaryAttributes_t& binaryAttributes)
{
    const auto initialFormat = binaryAttributes.format;

	for (const auto& analyzer : m_analyzers[initialFormat]) {
		analyzer->analyze(binary, binaryAttributes);
	}

    if (binaryAttributes.format != initialFormat) {
        run(binary, binaryAttributes);
    }
}

