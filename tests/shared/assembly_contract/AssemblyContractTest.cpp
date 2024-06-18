#include "shared/assembly_contract/instructions.hpp"
#include "shared/assembly_contract/operands.hpp"
#include "shared/assembly_contract/registers.hpp"
#include <shared/assembly_contract/code.hpp>
#include <gtest/gtest.h>

TEST(AssemblyContractTest, CanAssembleAssemblyContract)
{
    using namespace assembly::x86;

    auto codeBuilder = CodeBuilder { };
        
    auto code = codeBuilder
        .add(Instruction::MOV, Register::EAX, 1)
        .add(Instruction::RET)
        .code();


    ASSERT_EQ(code.size(), 2);
    ASSERT_EQ(code[0].instruction(), Instruction::MOV);
    ASSERT_EQ(code[0].operands().size(), 2);
    ASSERT_EQ(code[0].operands()[0]->type(), assembly::OperandType::REGISTER);
    ASSERT_EQ(code[0].operands()[0]->concrete<assembly::RegisterOperand<Register>>()->getRegister(), Register::EAX);
    ASSERT_EQ(code[0].operands()[1]->type(), assembly::OperandType::IMMEDIATE);
    auto c = code[0].operands()[1]->concrete<assembly::ImmediateOperand>();
    ASSERT_EQ(c->value(), 1);
    ASSERT_EQ(code[1].instruction(), Instruction::RET);
    ASSERT_EQ(code[1].operands().size(), 0);
}

