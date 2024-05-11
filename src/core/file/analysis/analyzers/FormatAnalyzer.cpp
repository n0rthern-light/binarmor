#include "FormatAnalyzer.hpp"
#include "../UnsupportedFileException.hpp"
#include <shared/self_obfuscation/strenc.hpp>

CFormatAnalyzer::CFormatAnalyzer(IEventBus* _eventBus): eventBus(_eventBus) { }

bool isWindowsPE(CBinary* binary)
{
	auto firstBytes = binary->getBytesAsString(0, 2);

	return firstBytes == "MZ";
}

void CFormatAnalyzer::analyze(CBinaryFile* binaryFile, AnalysisResult_t& result)
{
	auto binary = binaryFile->getBinary();

	if (isWindowsPE(&binary)) {
		result.format = Format::Windows_PE;
		return;
	}

	throw UnsupportedFileException(strenc("Not detected any supported file format!"));
}
