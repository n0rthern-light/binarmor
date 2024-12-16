#include "core/assembler/capstone/CapstoneDisassembler.hpp"
#include "core/assembler/defines.hpp"
#include "core/shared/attributes.hpp"
#include <gtest/gtest.h>

using namespace program::core::assembler::capstone;
using namespace program::core::shared;

TEST(CapstoneDisassemblerTest, DecodeX86Opcodes)
{
    auto disassembler = new CCapstoneDisassembler(Architecture::X86, Endianness::LITTLE);

    auto assembly = disassembler->disassemble({0x01, 0xD8, 0xC3});
    
    ASSERT_EQ(assembly, (program::core::assembler::asm_instructions {
        "add eax, ebx",
        "ret"
    }));
}

TEST(CapstoneDisassemblerTest, DecodeX86_64Opcodes)
{
    auto disassembler = new CCapstoneDisassembler(Architecture::X86_64, Endianness::LITTLE);

    auto assembly = disassembler->disassemble({0x48, 0x01, 0xD8, 0xC3});
    
    ASSERT_EQ(assembly, (program::core::assembler::asm_instructions {
        "add rax, rbx",
        "ret"
    }));
}

TEST(CapstoneDisassemblerTest, DecodeArm64Opcodes)
{
    auto disassembler = new CCapstoneDisassembler(Architecture::ARM64, Endianness::LITTLE);

    auto assembly = disassembler->disassemble({0x20, 0x00, 0x80, 0xD2, 0x41, 0x00, 0x80, 0xD2, 0x02, 0x00, 0x01, 0x8B, 0xC0, 0x03, 0x5F, 0xD6});
    
    ASSERT_EQ(assembly, (program::core::assembler::asm_instructions {
        "mov x0, #1",
        "mov x1, #2",
        "add x2, x0, x1",
        "ret",
    }));
}

