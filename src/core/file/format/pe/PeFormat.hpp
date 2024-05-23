#pragma once

#include "../IFormat.hpp"
#include "../../Binary.hpp"
#include "PeSection.hpp"
#include "PeImport.hpp"

class CPeFormat : public IFormat
{
	CBinary* binary;
public:
	CPeFormat(CBinary* _binary);
	Architecture architecture() const;
	Type type() const;
	Endianness endianness() const;
	AddressType addressType() const;
	CAddressValue entryPoint() const;
	pe_section_vec sections() const;
    pe_import_vec imports() const;
};

