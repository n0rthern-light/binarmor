#pragma once

#include "../Assembler.hpp"
#include "core/assembler/defines.hpp"
#include "core/shared/attributes.hpp"

namespace program::core::assembler::keystone {
    class CKeystoneAssembler : public IAssembler
    {
        program::core::shared::Architecture m_architecture;
        program::core::shared::Endianness m_endianness;
    public:
        CKeystoneAssembler(program::core::shared::Architecture architecture, program::core::shared::Endianness endianness);
        asm_opcodes assemble(const asm_instructions& input) override;
    };
}

