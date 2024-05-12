#include "TypeAnalyzer.hpp"
#include "../UnsupportedFileException.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <cassert>
#include "../../format/pe/PeFormat.hpp"

void CTypeAnalyzer::analyze(CBinaryFile* binaryFile, BinaryAttributes_t& attributes)
{
	auto binary = binaryFile->getBinary();

	assert(attributes.format != Format::UNKNOWN);

	if (attributes.format == Format::Windows_PE) {
		auto peBinary = CPeFormat(&binary);
		attributes.type = peBinary.getType();
	}

    if (attributes.type != Type::Executable && attributes.type != Type::Dynamic_Library) {
	    throw UnsupportedFileException(strenc("File type is not supported. Supported are Executable and Dynamic Library."));
    }
}
