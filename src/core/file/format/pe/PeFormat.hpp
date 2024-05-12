#pragma once

#include "../IFormat.hpp"
#include "../../Binary.hpp"

class CPeFormat : public IFormat
{
	CBinary* binary;
public:
	CPeFormat(CBinary* _binary);
	Architecture getArchitecture() const;
	Type getType() const;
};
