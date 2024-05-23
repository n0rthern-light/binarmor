#include "Binary.hpp"
#include "BinaryPointer.hpp"
#include <stdexcept>
#include <shared/self_obfuscation/strenc.hpp>

CBinary::CBinary(const byteVector_t bytes): _bytes(bytes) { }

CBinary CBinary::part(size_t offset, size_t count) const
{
	if (offset == 0 && count == 0) {
		return *this;
	}

	if (offset >= _bytes.size()) {
		throw std::out_of_range(strenc("Offset is out of the range of the data vector."));
	}

	if (count == 0 || offset + count > _bytes.size()) {
		count = _bytes.size() - offset;
	}

	auto subVector = byteVector_t(&_bytes[offset], &_bytes[offset + count]);

	return CBinary(subVector);
}

byteVector_t CBinary::bytes(size_t offset, size_t count) const {
	return part(offset, count)._bytes;
}

std::string CBinary::bytesAsString(size_t offset, size_t count) const
{
	auto vec = bytes(offset, count);
	
	return std::string(vec.begin(), vec.end());
}

size_t CBinary::size() const
{
	return _bytes.size();
}

CBinaryPointer CBinary::pointer(size_t offset) const
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

