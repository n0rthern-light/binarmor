#pragma once

#include <string>
#include "../types/defines.hpp"

class ICrypter
{
public:
    virtual ~ICrypter() { };
    virtual byte_vec xorBytes(const byte_vec& input, const std::string& key) const = 0;
    virtual std::string xorString(const std::string& input, const std::string& key) const = 0;
};
