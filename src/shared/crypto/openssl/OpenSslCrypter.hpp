#pragma once

#include "../ICrypter.hpp"

namespace program::shared::crypto::openssl
{
    class COpenSslCrypter : public ICrypter
    {
    public:
        program::shared::types::byte_vec xorBytes(const program::shared::types::byte_vec& input, const std::string& key) const;
        std::string xorString(const std::string& input, const std::string& key) const;
    };
}
