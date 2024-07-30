#ifndef SHARED_ASSEMBLY_CONTRACT_OPERANDS_HPP_
#define SHARED_ASSEMBLY_CONTRACT_OPERANDS_HPP_

#include <string>
#include <memory>
#include <variant>
#include "registers.hpp"

namespace assembly
{
    enum class OperandType {
        REGISTER,
        IMMEDIATE,
        MEMORY,
        LABEL
    };

    class Operand {
    public:
        virtual ~Operand() = default;
        OperandType type() const { return m_type; }
        template <typename T>
        T* concrete() {
            T* derived = dynamic_cast<T*>(this);
            if (derived == nullptr) {
                throw std::bad_cast();
            }
            return derived;
        }
    protected:
        OperandType m_type;
    };

    class CImmediateOperand : public Operand {
    public:
        CImmediateOperand(int value) : m_value(value) { m_type = OperandType::IMMEDIATE; }
        int value() const { return m_value; }
    private:
        int m_value;
    };

    class CLabelOperand : public Operand {
    public:
        CLabelOperand(const std::string& label) : m_label(label) { m_type = OperandType::LABEL; }
        std::string label() const { return m_label; }
    private:
        std::string m_label;
    };

    template <typename T>
    class CRegisterOperand : public Operand {
    public:
        CRegisterOperand(const T& t_register) : m_register(t_register) { m_type = OperandType::REGISTER; }
        T getRegister() const { return m_register; }
    private:
        T m_register;
    };

    template <typename T>
    class CMemoryOperand : public Operand {
    public:
        CMemoryOperand(const T& baseRegister, int offset) : m_baseRegister(baseRegister), m_offset(offset) { m_type = OperandType::MEMORY; }
        T baseRegister() const { return m_baseRegister; }
        int offset() const { return m_offset; }
    private:
        T m_baseRegister;
        int m_offset;
    };
}

#endif // SHARED_ASSEMBLY_CONTRACT_OPERANDS_HPP_
