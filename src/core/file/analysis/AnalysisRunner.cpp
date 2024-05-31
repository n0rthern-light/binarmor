#include "AnalysisRunner.hpp"
#include "analyzers/FormatAnalyzer.hpp"
#include "../../application/events/BinaryFileAnalyzedEvent.hpp"

CAnalysisRunner::CAnalysisRunner(IMessageBus* _eventBus): eventBus(_eventBus)
{
	analyzers = std::vector<IAnalyzer*>{
		new CFormatAnalyzer(eventBus),
	};
}

void CAnalysisRunner::run(CBinaryFile* binaryFile)
{
	BinaryAttributes_t attributes;

	for (auto analyzer : analyzers) {
		analyzer->analyze(binaryFile, attributes);
	}

	binaryFile->completeAnalysis(attributes);
	eventBus->publish(new CBinaryFileAnalyzedEvent());
}
