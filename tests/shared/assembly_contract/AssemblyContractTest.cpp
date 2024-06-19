#include "shared/assembly_contract/instructions.hpp"
#include "shared/assembly_contract/operands.hpp"
#include "shared/assembly_contract/registers.hpp"
#include <shared/assembly_contract/code.hpp>
#include <gtest/gtest.h>

TEST(AssemblyContractTest, CanAssembleAssemblyContract)
{
    using namespace assembly::x86;

    auto codeBuilder = CCodeBuilder { };
        
    auto code = codeBuilder
        .add(Instruction::MOV, Register::EAX, 1)
        .add(Instruction::RET)
        .code();

    ASSERT_EQ(code.size(), 2);
    ASSERT_EQ(code[0].instruction(), Instruction::MOV);
    ASSERT_EQ(code[0].operandCount(), 2);
    ASSERT_EQ(code[0].firstOperandType(), assembly::OperandType::REGISTER);
    ASSERT_EQ(code[0].firstOperandAs<assembly::CRegisterOperand<Register>>()->getRegister(), Register::EAX);
    ASSERT_EQ(code[0].secondOperandType(), assembly::OperandType::IMMEDIATE);
    ASSERT_EQ(code[0].secondOperandAs<assembly::CImmediateOperand>()->value(), 1);
    ASSERT_EQ(code[1].instruction(), Instruction::RET);
    ASSERT_EQ(code[1].operandCount(), 0);
}

