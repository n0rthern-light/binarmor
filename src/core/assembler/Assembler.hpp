#ifndef CORE_ASSEMBLER__ASSEMBLER_HPP_
#define CORE_ASSEMBLER__ASSEMBLER_HPP_

#include "defines.hpp"
#include "../attributes.hpp"

class IAssembler
{
public:
    virtual asm_opcodes assemble(Architecture arch, const asm_instructions& input) = 0;
    virtual ~IAssembler() { };
};

#endif // CORE_ASSEMBLER__ASSEMBLER_HPP_
