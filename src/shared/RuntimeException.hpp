#ifndef SHARED__RUNTIME_EXCEPTION_HPP_
#define SHARED__RUNTIME_EXCEPTION_HPP_

#include <stdexcept>

namespace program::shared
{
    class RuntimeException : public std::runtime_error {
    public:
        inline RuntimeException(const std::string& msg): std::runtime_error(msg) {};
    };
}

#endif // SHARED__RUNTIME_EXCEPTION_HPP_
