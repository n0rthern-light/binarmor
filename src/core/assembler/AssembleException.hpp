#ifndef CORE_ASSEMBLER__ASSEMBLE_EXCEPTION_HPP_
#define CORE_ASSEMBLER__ASSEMBLE_EXCEPTION_HPP_

#include <stdexcept>

using namespace std;

class AssembleException : public runtime_error {
public:
    inline AssembleException(const string& msg): runtime_error(msg) {};
};

#endif // CORE_ASSEMBLER__ASSEMBLE_EXCEPTION_HPP_
