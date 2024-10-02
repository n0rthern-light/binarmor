#pragma once

#include "core/assembler/Disassembler.hpp"
#include "core/assembler/defines.hpp"
#include "core/shared/attributes.hpp"

using namespace program::core::assembler;

class CCapstoneDisassembler : public IDisassembler
{
    Architecture m_architecture;
    Endianness m_endianness;
public:
    CCapstoneDisassembler(Architecture architecture, Endianness endianness);
    asm_instructions disassemble(const asm_opcodes& input) override;
};

