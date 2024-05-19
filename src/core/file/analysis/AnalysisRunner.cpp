#include "AnalysisRunner.hpp"
#include "analyzers/FormatAnalyzer.hpp"
#include "BinaryFileAnalyzedEvent.hpp"
#include "../format/pe/PeFormat.hpp"

CAnalysisRunner::CAnalysisRunner(IEventBus* _eventBus): eventBus(_eventBus)
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

	auto pe = new CPeFormat((CBinary*)&binaryFile->getBinary());
	pe->getArchitecture();
	pe->getSections();

	binaryFile->completeAnalysis(attributes);
	eventBus->publish(new CBinaryFileAnalyzedEvent());
}
