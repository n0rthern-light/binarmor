#include "ArchitectureAnalyzer.hpp"
#include "../UnsupportedFileException.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <cassert>
#include "../../format/pe/PeFormat.hpp"

void CArchitectureAnalyzer::analyze(CBinaryFile* binaryFile, BinaryAttributes_t& attributes)
{
	auto binary = binaryFile->getBinary();

	assert(attributes.format != Format::UNKNOWN);

	if (attributes.format == Format::Windows_PE) {
		auto peBinary = CPeFormat(&binary);
		attributes.architecture = peBinary.getArchitecture();
	}

    if (attributes.architecture != Architecture::X86 && attributes.architecture != Architecture::X86_64) {
	    throw UnsupportedFileException(strenc("File architecture is not supported"));
    }
}
