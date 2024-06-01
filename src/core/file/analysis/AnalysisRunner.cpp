#include "AnalysisRunner.hpp"
#include "analyzers/FormatAnalyzer.hpp"
#include "analyzers/PeAnalyzer.hpp"
#include "analyzers/HashAnalyzer.hpp"
#include "../../application/events/BinaryFileAnalyzedEvent.hpp"
#include "../../attributes.hpp"

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

void CAnalysisRunner::run(CBinaryFile* binaryFile)
{
    const auto initialFormat = binaryFile->format();
	auto attributes = binaryFile->attributes();

	for (const auto& analyzer : m_analyzers[initialFormat]) {
		analyzer->analyze(binaryFile, attributes);
	}

    if (binaryFile->format() != initialFormat) {
        run(binaryFile);
        return;
    }

	binaryFile->completeAnalysis(attributes);
	m_eventBus->publish(new CBinaryFileAnalyzedEvent());
}

