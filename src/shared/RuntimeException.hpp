#ifndef RUNTIME_EXCEPTION_H
#define RUNTIME_EXCEPTION_H

#include <stdexcept>

class RuntimeException : public std::runtime_error {
public:
    RuntimeException(const std::string& msg)
        : std::runtime_error(msg) {}
};

#endif