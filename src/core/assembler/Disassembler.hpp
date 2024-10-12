#pragma once

#include "../assembler/defines.hpp"

using namespace program::core::assembler;

class IDisassembler
{
public:
    virtual asm_instructions disassemble(const asm_opcodes& input) = 0;
    virtual ~IDisassembler() { };
};

