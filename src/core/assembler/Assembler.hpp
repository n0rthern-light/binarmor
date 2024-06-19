#pragma once

#include "../assembler/defines.hpp"
#include "../attributes.hpp"

class IAssembler
{
public:
    virtual asm_opcodes assemble(const asm_instructions& input) = 0;
    virtual ~IAssembler() { };
};
