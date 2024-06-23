#ifndef CORE_FORMAT_PE__PE_FORMAT_HPP_
#define CORE_FORMAT_PE__PE_FORMAT_HPP_

#include "../IFormat.hpp"
#include "../../Binary.hpp"
#include "PeSection.hpp"
#include "PeModule.hpp"
#include "../../BinaryPointer.hpp"
#include "../../shared/SectionPermissions.hpp"

class CPeFormat : public IFormat
{
    CBinary m_binary;
public:
    CPeFormat(const CBinary& binary);
    static std::unique_ptr<CPeFormat> create(const CBinary* binary);
    static std::unique_ptr<CPeFormat> create(const CBinary& binary);
    const CBinary* binary() const;
    Architecture architecture() const;
    Type type() const;
    Endianness endianness() const;
    AddressType addressType() const;
    CUnsigned entryPoint() const;
    binary_offset rvaToOffset(const binary_offset& rva) const;
    CBinaryPointer rvaToPointer(const binary_offset& rva) const;
    pe_section_vec sections() const;
    pe_module_map imports() const;
    void addSection(const std::string name, const CSectionPermissions permissions);
};

#endif // CORE_FORMAT_PE__PE_FORMAT_HPP_
