#ifndef CORE_ASSEMBLER__ASSEMBLE_EXCEPTION_HPP_
#define CORE_ASSEMBLER__ASSEMBLE_EXCEPTION_HPP_

#include <stdexcept>

namespace program::core::assembler {
    class AssembleException : public std::runtime_error {
    public:
        inline AssembleException(const std::string& msg): std::runtime_error(msg) {};
    };
}

#endif // CORE_ASSEMBLER__ASSEMBLE_EXCEPTION_HPP_
