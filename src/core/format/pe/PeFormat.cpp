#include "PeFormat.hpp"
#include "defines.hpp"
#include <shared/RuntimeException.hpp>
#include <shared/self_obfuscation/strenc.hpp>
#include "functions.hpp"

CPeFormat::CPeFormat(CBinary* binary)
{
	_binary = binary;
}

CBinary* CPeFormat::binary() const
{
    return _binary;
}

Architecture CPeFormat::architecture() const
{
	auto ntHeaders = format::pe::ntHeaders32(_binary);

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
	auto ntHeaders = format::pe::ntHeaders32(_binary);

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
	auto ntHeaders = format::pe::ntHeaders32(_binary);

	return ntHeaders->OptionalHeader.Magic == 0x20B ?
		AddressType::_64_BIT : AddressType::_32_BIT;
}

CUnsigned CPeFormat::entryPoint() const
{
	auto addressType_ = addressType();

	if (addressType_ == AddressType::_64_BIT)
	{
		return CUnsigned(format::pe::ntHeaders64(_binary)->OptionalHeader.AddressOfEntryPoint);
	}
	else if (addressType_ == AddressType::_32_BIT)
	{
		return CUnsigned(format::pe::ntHeaders32(_binary)->OptionalHeader.AddressOfEntryPoint);
	}

    throw RuntimeException(strenc("Not found entry point"));
}

pe_section_vec CPeFormat::sections() const
{
    return format::pe::readSectionList(this);
}

binary_offset CPeFormat::rvaToOffset(const binary_offset& rva) const
{
    return format::pe::rvaToOffset(this, rva);
}

CBinaryPointer CPeFormat::rvaToPointer(const binary_offset& rva) const
{
    return binary()->pointer(rvaToOffset(rva));
}

pe_module_map CPeFormat::imports() const
{
    return format::pe::readImportModules(this);
}

