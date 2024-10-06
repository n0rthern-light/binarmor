#ifndef CORE_FORMAT_PE__PE_FORMAT_HPP_
#define CORE_FORMAT_PE__PE_FORMAT_HPP_

#include "../IFormat.hpp"
#include "../../shared/Binary.hpp"
#include "PeSection.hpp"
#include "PeModule.hpp"
#include "../../shared/BinaryPointer.hpp"
#include "../../shared/SectionPermissions.hpp"
#include "core/format/IImport.hpp"
#include "core/format/IModule.hpp"
#include "core/shared/attributes.hpp"
#include "shared/types/defines.hpp"

class CPeFormat : public IFormat
{
    CBinary m_binary;
public:
    CPeFormat(const CPeFormat& other);
    CPeFormat(const CBinary& binary);
    Format format() const;
    CBinary binary() const;
    byte_vec bytes() const;
    Architecture architecture() const;
    Type type() const;
    Endianness endianness() const;
    AddressType addressType() const;
    CUnsigned entryPoint() const;
    binary_offset rvaToOffset(const binary_offset& rva) const;
    CBinaryPointer rvaToPointer(const binary_offset& rva) const;
    pe_section_vec peSections() const;
    uint_16 sectionCount() const;
    section_vec sections() const;
    pe_module_map peImportModules() const;
    module_map importModules() const;
    import_ptr import(const std::string& module, const std::string& function) const;
    CPeFormat addPeSection(
        const std::string& name,
        binary_offset size,
        const CSectionPermissions permissions
    ) const;
    format_ptr addSection(
        const std::string& name,
        binary_offset size,
        const CSectionPermissions permissions
    ) const;
    format_ptr changeBytes(
        const byte_vec& bytes
    ) const;
};

#endif // CORE_FORMAT_PE__PE_FORMAT_HPP_
