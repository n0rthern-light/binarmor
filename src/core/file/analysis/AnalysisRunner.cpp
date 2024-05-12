#include "AnalysisRunner.hpp"
#include "analyzers/FormatAnalyzer.hpp"
#include "analyzers/ArchitectureAnalyzer.hpp"
#include "analyzers/TypeAnalyzer.hpp"
#include "BinaryFileAnalyzedEvent.hpp"

CAnalysisRunner::CAnalysisRunner(IEventBus* _eventBus): eventBus(_eventBus)
{
	analyzers = std::vector<IAnalyzer*>{
		new CFormatAnalyzer(eventBus),
		new CArchitectureAnalyzer(eventBus),
		new CTypeAnalyzer(eventBus),
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
