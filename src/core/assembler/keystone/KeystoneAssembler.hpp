#ifndef CORE_ASSEMBLER_ASMJIT__ASM_JIT_ASSEMBLER_HPP_
#define CORE_ASSEMBLER_ASMJIT__ASM_JIT_ASSEMBLER_HPP_

#include "../Assembler.hpp"
#include "core/assembler/defines.hpp"
#include "core/shared/attributes.hpp"

using namespace program::core::assembler;

class KeystoneAssembler : public IAssembler
{
    Architecture m_architecture;
    Endianness m_endianness;
public:
    KeystoneAssembler(Architecture architecture, Endianness endianness);
    asm_opcodes assemble(const asm_instructions& input) override;
};

#endif // CORE_ASSEMBLER_ASMJIT__ASM_JIT_ASSEMBLER_HPP_
