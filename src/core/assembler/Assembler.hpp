#ifndef CORE_ASSEMBLER__ASSEMBLER_HPP_
#define CORE_ASSEMBLER__ASSEMBLER_HPP_

#include "../assembler/defines.hpp"

class IAssembler
{
public:
    virtual binarmor::core::assembler::asm_opcodes assemble(const binarmor::core::assembler::asm_instructions& input) = 0;
    virtual ~IAssembler() { };
};

#endif // CORE_ASSEMBLER__ASSEMBLER_HPP_
