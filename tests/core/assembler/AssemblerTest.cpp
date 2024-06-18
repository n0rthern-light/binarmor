#include "core/assembler/asmjit/AsmJitAssembler.hpp"
#include "core/assembler/defines.hpp"
#include "core/attributes.hpp"
#include <gtest/gtest.h>

auto assembler = new CAsmJitAssembler();

TEST(AssemblerTest, WillProduceCorrectOpcodes)
{
    auto opcodes = assembler->assemble(Architecture::X86, "mov eax, 1\nmov ebx, 2\nint 0x80\n");
    auto expected = asm_opcodes {0x50, 0x50, 0x50, 0x80};

    ASSERT_EQ(opcodes, expected);
}

