#include "OpenSslHasher.hpp"
#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>

using namespace program::shared::types;

std::string COpenSslHasher::sha256FromString(const std::string& str) const
{
    return sha256FromByteArray(reinterpret_cast<const unsigned char*>(str.data()), str.size());
}

std::string COpenSslHasher::sha256FromBytes(const byte_vec& vec) const
{
    return sha256FromByteArray(vec.data(), vec.size());
}

std::string COpenSslHasher::sha256FromByteArray(const byte_ptr data, binary_offset length) const
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, length);
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

