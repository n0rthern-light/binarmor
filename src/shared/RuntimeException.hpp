#ifndef SHARED__RUNTIME_EXCEPTION_HPP_
#define SHARED__RUNTIME_EXCEPTION_HPP_

#include <stdexcept>

using namespace std;

class RuntimeException : public runtime_error {
public:
    inline RuntimeException(const string& msg): runtime_error(msg) {};
};

#endif // SHARED__RUNTIME_EXCEPTION_HPP_
