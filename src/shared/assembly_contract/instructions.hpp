#ifndef SHARED_ASSEMBLY_CONTRACT_INSTRUCTIONS_HPP_
#define SHARED_ASSEMBLY_CONTRACT_INSTRUCTIONS_HPP_

#include <string>
#include <cstdint>

namespace assembly
{
    namespace x86
    {
        enum class Instruction {
            MOV,
            RET,
        };
    }

    namespace x86_64
    {
        enum class Instruction {
            MOV,
            RET,
        };
    }

    namespace arm64
    {
        enum class Instruction {
            MOV,
            RET,
        };
    }
}

#endif // SHARED_ASSEMBLY_CONTRACT_INSTRUCTIONS_HPP_
