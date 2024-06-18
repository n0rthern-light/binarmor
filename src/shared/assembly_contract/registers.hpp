#ifndef SHARED_ASSEMBLY_CONTRACT_REGISTERS_HPP_
#define SHARED_ASSEMBLY_CONTRACT_REGISTERS_HPP_

#include <string>
#include <cstdint>

namespace assembly
{
    namespace x86
    {
        enum class Register {
            EAX,
            EBX,
            ECX,
            EDX,
            ESI,
            EDI,
            ESP,
            EBP,
        };
    }

    namespace x86_64
    {
        enum class Register {
            RAX,
            RBX,
            RCX,
            RDX,
            RSI,
            RDI,
            RSP,
            RBP,
            R8,
            R9,
            R10,
            R11,
            R12,
            R13,
            R14,
            R15,
        };
    }

    namespace arm64
    {
        enum class Register {
            X0,
            X1,
            X2,
            X3,
            X4,
            X5,
            X6,
            X7,
            X8,
            X9,
            X10,
            X11,
            X12,
            X13,
            X14,
            X15,
            X16,
            X17,
            X18,
            X19,
            X20,
            X21,
            X22,
            X23,
            X24,
            X25,
            X26,
            X27,
            X28,
            X29,
            X30,
            SP,
        };
    }
}

#endif // SHARED_ASSEMBLY_CONTRACT_REGISTERS_HPP_
