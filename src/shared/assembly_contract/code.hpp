#ifndef SHARED_ASSEMBLY_CONTRACT_CODE_HPP_
#define SHARED_ASSEMBLY_CONTRACT_CODE_HPP_

#include <optional>
#include <vector>
#include "operands.hpp"
#include "instructions.hpp"

namespace assembly
{
    using vec_operand = std::vector<std::shared_ptr<Operand>>;

    template<typename T>
    class LineOfCode
    {
        T m_instruction;
        vec_operand m_vecOperand;

    public:
        LineOfCode(const T& instruction, vec_operand operands = { }): m_instruction(instruction), m_vecOperand(operands) { }
        T instruction() { return m_instruction; }
        vec_operand operands() { return m_vecOperand; }
    };

    template<typename T>
    class Code : public std::vector<LineOfCode<T>>
    {
    };

    namespace x86
    {
        class CodeBuilder
        {
            Code<assembly::x86::Instruction> m_code;
        public:
            CodeBuilder(const Code<assembly::x86::Instruction>& code = { }) : m_code(code) { }

            CodeBuilder& add(const assembly::x86::Instruction& instruction)
            {
                m_code.push_back(LineOfCode<assembly::x86::Instruction>(instruction));

                return *this;
            }

            CodeBuilder& add(const assembly::x86::Instruction& instruction, const assembly::x86::Register& reg, int immediate)
            {
                vec_operand operands;

                operands.push_back(std::make_shared<Operand>(assembly::RegisterOperand<assembly::x86::Register>(reg)));
                operands.push_back(std::make_shared<Operand>(assembly::ImmediateOperand(immediate)));

                m_code.push_back(LineOfCode<assembly::x86::Instruction>(instruction, operands));

                return *this;
            }

            CodeBuilder& add(const assembly::x86::Instruction& instruction, const assembly::x86::Register& reg1, const assembly::x86::Register& reg2)
            {
                vec_operand operands;

                operands.push_back(std::make_shared<Operand>(assembly::RegisterOperand<assembly::x86::Register>(reg1)));
                operands.push_back(std::make_shared<Operand>(assembly::RegisterOperand<assembly::x86::Register>(reg2)));

                m_code.push_back(LineOfCode<assembly::x86::Instruction>(instruction, operands));

                return *this;
            }

            Code<assembly::x86::Instruction> code() { return m_code; }
        };
    }
}

#endif // SHARED_ASSEMBLY_CONTRACT_CODE_HPP_
