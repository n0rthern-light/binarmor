#include "Binary.hpp"

CBinary::CBinary(const std::vector<unsigned char>& _bytes): bytes(_bytes) { }

const std::vector<unsigned char>& CBinary::getBytes() const {
    return bytes;
}
