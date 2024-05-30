#pragma once

#include <shared/RuntimeException.hpp>

class UnsupportedFileException : public RuntimeException
{
public:
	inline UnsupportedFileException(const string& msg) : RuntimeException(msg) { };
};
