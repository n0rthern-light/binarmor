#include "Binary.hpp"
#include "BinaryPointer.hpp"
#include <stdexcept>
#include <shared/self_obfuscation/strenc.hpp>
#include <shared/types/defines.hpp>
#include <stdio.h>

CBinary::CBinary(const byte_vec& bytes): _bytes(bytes) { }

byte_ptr CBinary::at(const binary_offset& offset) const
{
    return reinterpret_cast<byte_ptr>(&_bytes[offset]);
}

CBinary CBinary::part(const binary_offset& offset, const size_t& count) const
{
	if (offset == 0 && count == 0) {
		return *this;
	}

	if (offset >= _bytes.size()) {
		throw std::out_of_range(strenc("Offset is out of the range of the data vector."));
	}

    auto localCount = count;

	if (count == 0 || offset + count > _bytes.size()) {
		localCount = _bytes.size() - offset;
	}

	auto subVector = byte_vec(&_bytes[offset], &_bytes[offset + localCount]);

	return CBinary(subVector);
}

byte_vec CBinary::bytes() const {
	return _bytes;
}

std::string CBinary::string(const binary_offset& offset) const
{
    return std::string(reinterpret_cast<const char*>(at(offset)));
}

binary_offset CBinary::size() const
{
	return _bytes.size();
}

CBinaryPointer CBinary::pointer(const binary_offset& offset) const
{
	if (!offsetExists(offset)) {
        char message[128];
        sprintf(message, strenc("Out of range! Binary size is %u bytes, requested %u"), _bytes.size(), offset);
		throw std::out_of_range(message);
	}

	return CBinaryPointer(offset, reinterpret_cast<uint_auto>(&_bytes[offset]));
}

bool CBinary::offsetExists(const binary_offset& offset) const
{
    return offset >= 0 && offset < size();
}

std::string CBinary::hash(const IHasher* hasher) const
{
    return hasher->sha256FromBytes(_bytes);
}

bool CBinary::operator==(const CBinary& other) const
{
    if (size() != other.size()) {
        return false;
    }

    for(size_t i = 0; i < _bytes.size(); i++) {
        if (_bytes[i] != other._bytes[i]) {
            return false;
        }
    }

    return true;
}

