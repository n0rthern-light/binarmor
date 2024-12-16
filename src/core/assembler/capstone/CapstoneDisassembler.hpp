#pragma once

#include "core/assembler/Disassembler.hpp"
#include "core/assembler/defines.hpp"
#include "core/shared/attributes.hpp"

namespace program::core::assembler::capstone {
    class CCapstoneDisassembler : public IDisassembler
    {
        program::core::shared::Architecture m_architecture;
        program::core::shared::Endianness m_endianness;
    public:
        CCapstoneDisassembler(program::core::shared::Architecture architecture, program::core::shared::Endianness endianness);
        asm_instructions disassemble(const asm_opcodes& input) override;
    };
}

