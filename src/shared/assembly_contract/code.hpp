#ifndef SHARED_ASSEMBLY_CONTRACT_CODE_HPP_
#define SHARED_ASSEMBLY_CONTRACT_CODE_HPP_

#include "operands.hpp"
#include "instructions.hpp"
#include "../RuntimeException.hpp"
#include "../self_obfuscation/strenc.hpp"
#include <optional>
#include <vector>
#include <type_traits>

namespace assembly
{
    enum class Architecture
    {
        X86,
        X86_64,
        ARM64,
    };

    using operand_ptr = std::shared_ptr<Operand>;
    using vec_operand = std::vector<operand_ptr>;

    template<typename T>
    class CLineOfCode
    {
        T m_instruction;
        vec_operand m_vecOperand;

    public:
        CLineOfCode(const T& instruction, vec_operand operands = { }): m_instruction(instruction), m_vecOperand(operands) { }
        T instruction() { return m_instruction; }
        vec_operand operands() { return m_vecOperand; }
        size_t operandCount() { return m_vecOperand.size(); }
        operand_ptr firstOperand() { if (operandCount() < 1) { throw RuntimeException(strenc("First operand not present")); } return m_vecOperand[0]; }
        operand_ptr secondOperand() { if (operandCount() < 2) { throw RuntimeException(strenc("Second operand not present")); } return m_vecOperand[1]; }
        assembly::OperandType firstOperandType() { return firstOperand()->type(); }
        assembly::OperandType secondOperandType() { return secondOperand()->type(); }
        template<typename X>
        X* firstOperandAs() { return firstOperand()->template concrete<X>(); }
        template<typename X>
        X* secondOperandAs() { return secondOperand()->template concrete<X>(); }
    };

    class ICode
    {
    public:
        virtual ~ICode() { };
        virtual assembly::Architecture arch() const = 0;
    };

    template<typename T>
    class CCode : public std::vector<CLineOfCode<T>>, public ICode
    {
    public:
        assembly::Architecture arch() const
        {
            if constexpr (std::is_same_v<T, assembly::x86::Instruction>) {
                return assembly::Architecture::X86;
            } else if constexpr (std::is_same_v<T, assembly::x86_64::Instruction>) {
                return assembly::Architecture::X86_64;
            } else if constexpr (std::is_same_v<T, assembly::arm64::Instruction>) {
                return assembly::Architecture::ARM64;
            } else {
                throw RuntimeException(strenc("Unsupported architecture"));
            }
        }
    };

    namespace x86
    {
        class CCodeBuilder
        {
            CCode<assembly::x86::Instruction> m_code;
        public:
            CCodeBuilder(const CCode<assembly::x86::Instruction>& code = { }) : m_code(code) { }

            CCodeBuilder& add(const assembly::x86::Instruction& instruction)
            {
                m_code.push_back(CLineOfCode<assembly::x86::Instruction>(instruction));

                return *this;
            }

            CCodeBuilder& add(const assembly::x86::Instruction& instruction, const assembly::x86::Register& reg, int immediate)
            {
                vec_operand operands;

                operands.push_back(std::make_shared<assembly::CRegisterOperand<assembly::x86::Register>>(reg));
                operands.push_back(std::make_shared<assembly::CImmediateOperand>(immediate));

                m_code.push_back(CLineOfCode<assembly::x86::Instruction>(instruction, operands));

                return *this;
            }

            CCodeBuilder& add(const assembly::x86::Instruction& instruction, const assembly::x86::Register& reg1, const assembly::x86::Register& reg2)
            {
                vec_operand operands;

                operands.push_back(std::make_shared<assembly::CRegisterOperand<assembly::x86::Register>>(reg1));
                operands.push_back(std::make_shared<assembly::CRegisterOperand<assembly::x86::Register>>(reg2));

                m_code.push_back(CLineOfCode<assembly::x86::Instruction>(instruction, operands));

                return *this;
            }

            CCode<assembly::x86::Instruction> code() { return m_code; }
        };
    }
}

#endif // SHARED_ASSEMBLY_CONTRACT_CODE_HPP_
