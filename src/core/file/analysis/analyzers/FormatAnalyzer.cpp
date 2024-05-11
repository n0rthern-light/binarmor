#include "FormatAnalyzer.hpp"

CFormatAnalyzer::CFormatAnalyzer(IEventBus* _eventBus): eventBus(_eventBus) { }

void CFormatAnalyzer::analyze(CBinaryFile* binaryFile, AnalysisResult_t& result)
{
	result.format = Format::Windows_PE;
}
