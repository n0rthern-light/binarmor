#ifndef CORE_ASSEMBLER_ASMJIT__ASM_JIT_ASSEMBLER_HPP_
#define CORE_ASSEMBLER_ASMJIT__ASM_JIT_ASSEMBLER_HPP_

#include "../Assembler.hpp"

class CAsmJitAssembler : public IAssembler
{
public:
    asm_opcodes assemble(Architecture arch, const asm_instructions& input) override;
};

#endif // CORE_ASSEMBLER_ASMJIT__ASM_JIT_ASSEMBLER_HPP_
