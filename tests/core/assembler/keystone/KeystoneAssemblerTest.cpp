#include "core/assembler/keystone/KeystoneAssembler.hpp"
#include "core/assembler/defines.hpp"
#include "core/shared/attributes.hpp"
#include <gtest/gtest.h>

TEST(KeystoneAssemblerTest, ProduceX86Opcodes)
{
    auto assembler = new CKeystoneAssembler(Architecture::X86, Endianness::LITTLE);

    auto opcodes = assembler->assemble({
        "add eax, ebx",
        "ret"
    });
    
    ASSERT_EQ(opcodes, (program::core::assembler::asm_opcodes {0x01, 0xD8, 0xC3}));
}

TEST(KeystoneAssemblerTest, ProduceX86_64Opcodes)
{
    auto assembler = new CKeystoneAssembler(Architecture::X86_64, Endianness::LITTLE);

    auto opcodes = assembler->assemble({
        "add rax, rbx",
        "ret"
    });
    
    ASSERT_EQ(opcodes, (program::core::assembler::asm_opcodes {0x48, 0x01, 0xD8, 0xC3}));
}

TEST(KeystoneAssemblerTest, ProduceArm64Opcodes)
{
    auto assembler = new CKeystoneAssembler(Architecture::ARM64, Endianness::LITTLE);

    auto opcodes = assembler->assemble({
        "mov x0, #1",
        "mov x1, #2",
        "add x2, x0, x1",
        "ret",
    });
    
    ASSERT_EQ(opcodes, (program::core::assembler::asm_opcodes {0x20, 0x00, 0x80, 0xD2, 0x41, 0x00, 0x80, 0xD2, 0x02, 0x00, 0x01, 0x8B, 0xC0, 0x03, 0x5F, 0xD6}));
}

