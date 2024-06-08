#ifndef SRC_SHARED_CRYPTO__I_HASHER_HPP_
#define SRC_SHARED_CRYPTO__I_HASHER_HPP_





#include <string>
#include "../types/defines.hpp"

class IHasher
{
public:
    ~IHasher() { };
    virtual std::string sha256FromString(const std::string& str) const = 0;
    virtual std::string sha256FromBytes(const byte_vec& vec) const = 0;
};




#endif // SRC_SHARED_CRYPTO__I_HASHER_HPP_
