#pragma once

#include "../ICrypter.hpp"

class COpenSslCrypter : public ICrypter
{
public:
    byte_vec xorBytes(const byte_vec& input, const std::string& key) const;
    std::string xorString(const std::string& input, const std::string& key) const;
};
