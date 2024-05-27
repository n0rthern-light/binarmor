#pragma once

#include "../IFormat.hpp"
#include "../../Binary.hpp"
#include "PeSection.hpp"
#include "PeImport.hpp"
#include "core/file/BinaryPointer.hpp"

class CPeFormat : public IFormat
{
	CBinary* _binary;
public:
	CPeFormat(CBinary* binary);
    CBinary* binary() const;
	Architecture architecture() const;
	Type type() const;
	Endianness endianness() const;
	AddressType addressType() const;
	CAddressValue entryPoint() const;
    binary_offset rvaToOffset(const binary_offset& rva) const;
    CBinaryPointer rvaToPointer(const binary_offset& rva) const;
	pe_section_vec sections() const;
    pe_import_vec imports() const;
};

