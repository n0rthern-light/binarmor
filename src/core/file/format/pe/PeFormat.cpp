#include "PeFormat.hpp"
#include "PeSection.hpp"
#include "defines.hpp"
#include <cassert>
#include <shared/RuntimeException.hpp>
#include <shared/self_obfuscation/strenc.hpp>

CPeFormat::CPeFormat(CBinary* _binary)
{
	binary = _binary;
}

void assertBinaryNotNull(CBinary* binary)
{
	if (!binary) {
		throw RuntimeException(strenc("Binary is not present"));
    }
}

IMAGE_DOS_HEADER* getDosHeader(CBinary* binary)
{
	assertBinaryNotNull(binary);

    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(binary->pointer(0).ptr());

    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		throw RuntimeException(strenc("Invalid IMAGE_DOS_SIGNATURE"));
    }

	return dosHeader;
}

IMAGE_NT_HEADERS32* getNtHeaders32(CBinary* binary)
{
	assertBinaryNotNull(binary);

	auto dosHeader = getDosHeader(binary);

    IMAGE_NT_HEADERS32* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS32*>(binary->pointer(dosHeader->e_lfanew).ptr());

    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
		throw RuntimeException(strenc("Invalid IMAGE_NT_SIGNATURE"));
    }

	return ntHeaders;
}

IMAGE_NT_HEADERS64* getNtHeaders64(CBinary* binary)
{
	assertBinaryNotNull(binary);

	auto dosHeader = getDosHeader(binary);

    IMAGE_NT_HEADERS64* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS64*>(binary->pointer(dosHeader->e_lfanew).ptr());

    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
		throw RuntimeException(strenc("Invalid IMAGE_NT_SIGNATURE"));
    }

	return ntHeaders;
}

Architecture CPeFormat::architecture() const
{
	auto ntHeaders = getNtHeaders32(binary);

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
		throw RuntimeException(strenc("Unknown Architecture"));
    }
}

Type CPeFormat::type() const
{
	auto ntHeaders = getNtHeaders32(binary);

    if (ntHeaders->FileHeader.Characteristics & IMAGE_FILE_DLL) {
        return Type::Dynamic_Library;
    }
    else if (ntHeaders->FileHeader.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) {
        return Type::Executable;
    }

	throw RuntimeException(strenc("Unknown Type"));
}

Endianness CPeFormat::endianness() const
{
	// PE is always Little Endian
	return Endianness::LITTLE;
}

AddressType CPeFormat::addressType() const
{
	auto ntHeaders = getNtHeaders32(binary);

	return ntHeaders->OptionalHeader.Magic == 0x20B ?
		AddressType::_64_BIT : AddressType::_32_BIT;
}

CAddressValue CPeFormat::entryPoint() const
{
	auto addressType_ = addressType();

	if (addressType_ == AddressType::_64_BIT)
	{
		return CAddressValue(getNtHeaders64(binary)->OptionalHeader.AddressOfEntryPoint);
	}
	else if (addressType_ == AddressType::_32_BIT)
	{
		return CAddressValue(getNtHeaders32(binary)->OptionalHeader.AddressOfEntryPoint);
	}
}

std::vector<std::shared_ptr<CPeSection>> CPeFormat::sections() const
{
	auto vec = std::vector<std::shared_ptr<CPeSection>>();
	auto addressType_ = addressType();
	auto dosHeader = getDosHeader(binary);

	if (addressType_ == AddressType::_64_BIT)
	{
		auto ntHeaders = getNtHeaders64(binary);
		auto offset = dosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS64);
		auto binaryPointer = binary->pointer(offset);
		auto sectionHeader = reinterpret_cast<IMAGE_SECTION_HEADER*>(binaryPointer.ptr());

		for(int i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i)
		{
			auto section = std::make_shared<CPeSection>(sectionHeader[i]);
			vec.push_back(section);
		}
	}
	else if (addressType_ == AddressType::_32_BIT)
	{
		auto ntHeaders = getNtHeaders32(binary);
		auto offset = dosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS32);
		auto binaryPointer = binary->pointer(offset);
		auto sectionHeader = reinterpret_cast<IMAGE_SECTION_HEADER*>(binaryPointer.ptr());

		for(int i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i)
		{
			auto section = std::make_shared<CPeSection>(sectionHeader[i]);
			vec.push_back(section);
		}
	}

	return vec;
}

