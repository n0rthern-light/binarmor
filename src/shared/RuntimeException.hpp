#pragma once

#include <stdexcept>

using namespace std;

class RuntimeException : public runtime_error {
public:
    inline RuntimeException(const string& msg): runtime_error(msg) {};
};
