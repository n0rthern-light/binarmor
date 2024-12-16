#ifndef CORE_MODIFICATION__MODIFICATION_EXCEPTION_HPP_
#define CORE_MODIFICATION__MODIFICATION_EXCEPTION_HPP_

#include <stdexcept>

using namespace std;

namespace program::core::modification {
    class ModificationException : public runtime_error {
    public:
        inline ModificationException(const string& msg): runtime_error(msg) {};
    };
}

#endif // CORE_MODIFICATION__MODIFICATION_EXCEPTION_HPP_
