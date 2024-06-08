#ifndef SRC_SHARED__RUNTIME_EXCEPTION_HPP_
#define SRC_SHARED__RUNTIME_EXCEPTION_HPP_





#include <stdexcept>

using namespace std;

class RuntimeException : public runtime_error {
public:
    inline RuntimeException(const string& msg): runtime_error(msg) {};
};



#endif // SRC_SHARED__RUNTIME_EXCEPTION_HPP_
