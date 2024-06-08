#ifndef SHARED_CRYPTO_OPENSSL__OPEN_SSL_HASHER_HPP_
#define SHARED_CRYPTO_OPENSSL__OPEN_SSL_HASHER_HPP_

#include "../IHasher.hpp"

class COpenSslHasher : public IHasher
{
public:
    std::string sha256FromString(const std::string& str) const;
    std::string sha256FromBytes(const byte_vec& vec) const;
    std::string sha256FromByteArray(const byte_ptr data, binary_offset length) const;
};

#endif // SHARED_CRYPTO_OPENSSL__OPEN_SSL_HASHER_HPP_
