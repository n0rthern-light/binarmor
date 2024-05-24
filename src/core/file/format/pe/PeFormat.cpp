#include "PeFormat.hpp"
#include "PeSection.hpp"
#include "defines.hpp"
#include <cassert>
#include <shared/RuntimeException.hpp>
#include <shared/self_obfuscation/strenc.hpp>
#include "functions.hpp"

CPeFormat::CPeFormat(CBinary* _binary)
{
	binary = _binary;
}

Architecture CPeFormat::architecture() const
{
	auto ntHeaders = format::pe::ntHeaders32(binary);

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
	auto ntHeaders = format::pe::ntHeaders32(binary);

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
	auto ntHeaders = format::pe::ntHeaders32(binary);

	return ntHeaders->OptionalHeader.Magic == 0x20B ?
		AddressType::_64_BIT : AddressType::_32_BIT;
}

CAddressValue CPeFormat::entryPoint() const
{
	auto addressType_ = addressType();

	if (addressType_ == AddressType::_64_BIT)
	{
		return CAddressValue(format::pe::ntHeaders64(binary)->OptionalHeader.AddressOfEntryPoint);
	}
	else if (addressType_ == AddressType::_32_BIT)
	{
		return CAddressValue(format::pe::ntHeaders32(binary)->OptionalHeader.AddressOfEntryPoint);
	}

    throw RuntimeException(strenc("Not found entry point"));
}

pe_section_vec CPeFormat::sections() const
{
    return CPeSection::readList(binary, addressType());
}

pe_import_vec CPeFormat::imports() const
{
    return CPeImport::readList(binary, addressType());
}

