#include "FormatAnalyzer.hpp"
#include "../UnsupportedFileException.hpp"
#include <shared/self_obfuscation/strenc.hpp>

bool isWindowsPE(const CBinary* binary) {
    auto firstBytes = binary->getBytesAsString(0, 2);

    return firstBytes == strenc("MZ");
}

bool isELF(const CBinary* binary) {
    auto firstBytes = binary->getBytesAsString(0, 4);

    return firstBytes.size() >= 4 && firstBytes[0] == strenc('0x7F') && firstBytes.substr(1, 3) == strenc("ELF");
}

bool isMachO(const CBinary* binary) {
    auto firstBytes = binary->getBytesAsString(0, 4);

    if (firstBytes.size() < 4) {
        return false;
    }

    uint32_t magic = *reinterpret_cast<const uint32_t*>(firstBytes.data());

    return magic == 0xFEEDFACE || magic == 0xFEEDFACF || magic == 0xCAFEBABE;
}

void CFormatAnalyzer::analyze(CBinaryFile* binaryFile, BinaryAttributes_t& attributes)
{
	auto binary = binaryFile->getBinary();

    if (isWindowsPE(&binary)) {
        attributes.format = Format::Windows_PE;
    }
    else if (isELF(&binary)) {
        attributes.format = Format::Linux_ELF;
    }
    else if (isMachO(&binary)) {
        attributes.format = Format::MacOS_MachO;
    }

    if (attributes.format != Format::Windows_PE) {
	    throw UnsupportedFileException(strenc("Not detected any supported file format"));
    }
}
