#ifndef SHARED_CRYPTO__I_HASHER_HPP_
#define SHARED_CRYPTO__I_HASHER_HPP_

#include <string>
#include "../types/defines.hpp"

class IHasher
{
public:
    ~IHasher() { };
    virtual std::string sha256FromString(const std::string& str) const = 0;
    virtual std::string sha256FromBytes(const byte_vec& vec) const = 0;
};

#endif // SHARED_CRYPTO__I_HASHER_HPP_
