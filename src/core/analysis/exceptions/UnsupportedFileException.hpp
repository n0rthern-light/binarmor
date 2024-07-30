#ifndef CORE_ANALYSIS_EXCEPTIONS__UNSUPPORTED_FILE_EXCEPTION_HPP_
#define CORE_ANALYSIS_EXCEPTIONS__UNSUPPORTED_FILE_EXCEPTION_HPP_

#include <shared/RuntimeException.hpp>

class UnsupportedFileException : public RuntimeException
{
public:
    inline UnsupportedFileException(const string& msg) : RuntimeException(msg) { };
};

#endif // CORE_ANALYSIS_EXCEPTIONS__UNSUPPORTED_FILE_EXCEPTION_HPP_
