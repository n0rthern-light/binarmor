#include "AnalysisRunner.hpp"
#include "analyzers/FormatAnalyzer.hpp"
#include "BinaryFileAnalyzedEvent.hpp"

CAnalysisRunner::CAnalysisRunner(IEventBus* _eventBus): eventBus(_eventBus)
{
	analyzers = std::vector<IAnalyzer*>{
		new CFormatAnalyzer(eventBus)
	};
}

void CAnalysisRunner::run(CBinaryFile* binaryFile)
{
	auto result = AnalysisResult_t();

	for (auto analysis : analyzers) {
		analysis->analyze(binaryFile, result);
	}

	binaryFile->applyAnalysis(result);
	eventBus->publish(new CBinaryFileAnalyzedEvent());
}
