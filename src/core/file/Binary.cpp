#include "Binary.hpp"
#include "BinaryPointer.hpp"
#include <stdexcept>
#include <shared/self_obfuscation/strenc.hpp>

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

    size_t localCount = count;

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

size_t CBinary::size() const
{
	return _bytes.size();
}

CBinaryPointer CBinary::pointer(const binary_offset& offset) const
{
	if (offset >= _bytes.size()) {
		throw std::out_of_range(strenc("Offset is out of the range of the data vector."));
	}

	return CBinaryPointer(offset, reinterpret_cast<std::uintptr_t>(&_bytes[offset]));
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

