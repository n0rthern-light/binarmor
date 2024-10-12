#ifndef CORE_ASSEMBLER_DEFINES_HPP_
#define CORE_ASSEMBLER_DEFINES_HPP_

#include <vector>
#include <string>
#include <shared/types/defines.hpp>

namespace program
{
    namespace core
    {
        namespace assembler
        {
            using asm_instructions = std::vector<std::string>;
            using asm_opcodes = byte_vec;
        }
    }
}

#endif // CORE_ASSEMBLER_DEFINES_HPP_
