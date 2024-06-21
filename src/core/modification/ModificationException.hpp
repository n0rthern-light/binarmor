#pragma once

#include <stdexcept>

using namespace std;

class ModificationException : public runtime_error {
public:
    inline ModificationException(const string& msg): runtime_error(msg) {};
};

