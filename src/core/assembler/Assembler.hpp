#ifndef CORE_ASSEMBLER__ASSEMBLER_HPP_
#define CORE_ASSEMBLER__ASSEMBLER_HPP_

#include "../assembler/defines.hpp"

using namespace program::core::assembler;

class IAssembler
{
public:
    virtual asm_opcodes assemble(const asm_instructions& input) = 0;
    virtual ~IAssembler() { };
};

#endif // CORE_ASSEMBLER__ASSEMBLER_HPP_
