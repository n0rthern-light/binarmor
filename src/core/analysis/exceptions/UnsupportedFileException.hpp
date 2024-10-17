#ifndef CORE_ANALYSIS_EXCEPTIONS__UNSUPPORTED_FILE_EXCEPTION_HPP_
#define CORE_ANALYSIS_EXCEPTIONS__UNSUPPORTED_FILE_EXCEPTION_HPP_

#include <shared/RuntimeException.hpp>

namespace program::core::analysis::exceptions {
    class UnsupportedFileException : public program::shared::RuntimeException
    {
    public:
        inline UnsupportedFileException(const std::string& msg) : program::shared::RuntimeException(msg) { };
    };
}

#endif // CORE_ANALYSIS_EXCEPTIONS__UNSUPPORTED_FILE_EXCEPTION_HPP_
