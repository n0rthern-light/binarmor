#pragma once

#include <string>
#include "../types/defines.hpp"

class IHasher
{
public:
    ~IHasher() { };
    virtual std::string sha256FromString(const std::string& str) const = 0;
    virtual std::string sha256FromBytes(const byte_vec& vec) const = 0;
};

