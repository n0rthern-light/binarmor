#pragma once

#include "../Assembler.hpp"
#include "core/assembler/defines.hpp"
#include "core/shared/attributes.hpp"

using namespace program::core::assembler;

class CKeystoneAssembler : public IAssembler
{
    Architecture m_architecture;
    Endianness m_endianness;
public:
    CKeystoneAssembler(Architecture architecture, Endianness endianness);
    asm_opcodes assemble(const asm_instructions& input) override;
};

