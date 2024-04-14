#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>

class Exception : public std::runtime_error {
public:
    Exception(const std::string& msg)
        : std::runtime_error(msg) {}
};

#endif