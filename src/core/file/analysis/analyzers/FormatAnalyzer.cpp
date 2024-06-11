#include "FormatAnalyzer.hpp"
#include "../exceptions/UnsupportedFileException.hpp"
#include "core/Binary.hpp"
#include "core/attributes.hpp"
#include <shared/self_obfuscation/strenc.hpp>

bool isWindowsPE(const CBinary* binary) {
    auto firstBytes = binary->part(0, 2).string();

    return firstBytes == strenc("MZ");
}

bool isELF(const CBinary* binary) {
    auto firstBytes = binary->part(0, 4).string();

    return firstBytes.size() >= 4 && firstBytes[0] == strenc('0x7F') && firstBytes.substr(1, 3) == strenc("ELF");
}

bool isMachO(const CBinary* binary) {
    auto firstBytes = binary->part(0, 4).string();

    if (firstBytes.size() < 4) {
        return false;
    }

    uint32_t magic = *reinterpret_cast<const uint32_t*>(firstBytes.data());

    return magic == 0xFEEDFACE || magic == 0xFEEDFACF || magic == 0xCAFEBABE;
}

void CFormatAnalyzer::analyze(const CBinary* binary, BinaryAttributes_t& attributes)
{
    if (isWindowsPE(binary)) {
        attributes.format = Format::Windows_PE;
    }
    else if (isELF(binary)) {
        // attributes.format = Format::Linux_ELF;
    }
    else if (isMachO(binary)) {
        // attributes.format = Format::MacOS_MachO;
    }

    if (attributes.format == Format::UNKNOWN) {
        throw UnsupportedFileException(strenc("The choosen file has a format that is not supported."));
    }
}

