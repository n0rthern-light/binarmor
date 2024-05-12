#include "PeFormat.hpp"
#include "defines.hpp"

CPeFormat::CPeFormat(CBinary* _binary)
{
	binary = _binary;
}

Architecture CPeFormat::getArchitecture() const {
    if (!binary) {
        return Architecture::UNKNOWN;
    }

    auto dosHeaderBytes = binary->getBytes(0, sizeof(IMAGE_DOS_HEADER));
    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(dosHeaderBytes.data());

    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        return Architecture::UNKNOWN;
    }

    auto peHeaderBytes = binary->getBytes(dosHeader->e_lfanew, sizeof(IMAGE_NT_HEADERS));
    IMAGE_NT_HEADERS* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(peHeaderBytes.data());

    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
        return Architecture::UNKNOWN;
    }

    switch (ntHeaders->FileHeader.Machine) {
    case IMAGE_FILE_MACHINE_I386:
        return Architecture::X86;
    case IMAGE_FILE_MACHINE_AMD64:
        return Architecture::X86_64;
    case IMAGE_FILE_MACHINE_ARM:
        return Architecture::ARM;
    case IMAGE_FILE_MACHINE_ARM64:
        return Architecture::ARM64;
    default:
        return Architecture::UNKNOWN;
    }
}

Type CPeFormat::getType() const {
    if (!binary) {
        return Type::UNKNOWN;
    }

    auto dosHeaderBytes = binary->getBytes(0, sizeof(IMAGE_DOS_HEADER));
    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(dosHeaderBytes.data());

    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        return Type::UNKNOWN;
    }

    auto peHeaderBytes = binary->getBytes(dosHeader->e_lfanew, sizeof(IMAGE_NT_HEADERS));
    IMAGE_NT_HEADERS* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(peHeaderBytes.data());

    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
        return Type::UNKNOWN;
    }

    if (ntHeaders->FileHeader.Characteristics & IMAGE_FILE_DLL) {
        return Type::Dynamic_Library;
    }
    else if (ntHeaders->FileHeader.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) {
        return Type::Executable;
    }

    return Type::UNKNOWN;
}
