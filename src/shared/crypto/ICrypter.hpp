#pragma once

#include <string>
#include "../types/defines.hpp"

namespace program::shared::crypto
{
    class ICrypter
    {
    public:
        virtual ~ICrypter() { };
        virtual program::shared::types::byte_vec xorBytes(const program::shared::types::byte_vec& input, const std::string& key) const = 0;
        virtual std::string xorString(const std::string& input, const std::string& key) const = 0;
    };
}
