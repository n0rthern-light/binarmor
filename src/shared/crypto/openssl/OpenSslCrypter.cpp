#include "OpenSslCrypter.hpp"
#include "../../self_obfuscation/strenc.hpp"
#include <cstring>
#include <string>

using namespace program::shared::types;

byte_vec COpenSslCrypter::xorBytes(const byte_vec& input, const std::string& key) const
{
    auto output = input;
    auto i = 0;
    for (auto& item : output) {
        item = item ^ key[i % key.size()];
        ++i;
    }

    return output;
}

std::string COpenSslCrypter::xorString(const std::string& input, const std::string& key) const
{
    byte_vec inputBytes(input.begin(), input.end());
    byte_vec outputBytes = xorBytes(inputBytes, key);
    
    return std::string(outputBytes.begin(), outputBytes.end());
}
