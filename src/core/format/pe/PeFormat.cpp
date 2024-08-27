#include "PeFormat.hpp"
#include "core/format/IFormat.hpp"
#include "core/format/IModule.hpp"
#include "core/format/pe/PeSection.hpp"
#include "defines.hpp"
#include <memory>
#include <shared/RuntimeException.hpp>
#include <shared/self_obfuscation/strenc.hpp>
#include "functions.hpp"

CPeFormat::CPeFormat(const CPeFormat& other): m_binary(other.binary()) { }

CPeFormat::CPeFormat(const CBinary& binary): m_binary(binary) { }

CBinary CPeFormat::binary() const
{
    return m_binary;
}

byte_vec CPeFormat::bytes() const
{
    return binary().bytes();
}

Architecture CPeFormat::architecture() const
{
    auto ntHeaders = format::pe::ntHeaders32(m_binary);

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
    auto ntHeaders = format::pe::ntHeaders32(m_binary);

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
    auto ntHeaders = format::pe::ntHeaders32(m_binary);

    return ntHeaders->OptionalHeader.Magic == 0x20B ?
        AddressType::_64_BIT : AddressType::_32_BIT;
}

CUnsigned CPeFormat::entryPoint() const
{
    auto addressType_ = addressType();

    if (addressType_ == AddressType::_64_BIT)
    {
        return CUnsigned(format::pe::ntHeaders64(m_binary)->OptionalHeader.AddressOfEntryPoint);
    }
    else if (addressType_ == AddressType::_32_BIT)
    {
        return CUnsigned(format::pe::ntHeaders32(m_binary)->OptionalHeader.AddressOfEntryPoint);
    }

    throw RuntimeException(strenc("Not found entry point"));
}

pe_section_vec CPeFormat::peSections() const
{
    return format::pe::readSectionList(*this);
}

uint_16 CPeFormat::sectionCount() const
{
    return format::pe::numberOfSections(*this);
}

section_vec CPeFormat::sections() const
{
    const auto pe = peSections();
    auto res = section_vec { };
    res.reserve(pe.size());

    for (const auto& section : pe) {
        res.push_back(std::static_pointer_cast<ISection>(section));
    }

    return res;
}

binary_offset CPeFormat::rvaToOffset(const binary_offset& rva) const
{
    return format::pe::rvaToOffset(*this, rva);
}

CBinaryPointer CPeFormat::rvaToPointer(const binary_offset& rva) const
{
    return binary().pointer(rvaToOffset(rva));
}

pe_module_map CPeFormat::peImportModules() const
{
    return format::pe::readImportModules(*this);
}

module_map CPeFormat::importModules() const
{
    const auto pe = peImportModules();
    auto res = module_map { };

    for (const auto& keyVal : pe) {
        res[keyVal.first] = std::static_pointer_cast<IModule>(keyVal.second);
    }

    return res;
}

CPeFormat CPeFormat::addPeSection(
    const std::string& name,
    binary_offset size,
    const CSectionPermissions permissions
) const {
    return format::pe::addSection(*this, name, size, permissions);
}

format_ptr CPeFormat::addSection(
    const std::string& name,
    binary_offset size,
    const CSectionPermissions permissions
) const {
    return std::make_shared<CPeFormat>(addPeSection(name, size, permissions));
}

format_ptr CPeFormat::changeBytes(
    const byte_vec& bytes
) const {
    return std::make_shared<CPeFormat>(bytes);
}

