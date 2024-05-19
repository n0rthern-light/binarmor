#include "Binary.hpp"
#include <stdexcept>
#include <shared/self_obfuscation/strenc.hpp>

CBinary::CBinary(const std::vector<unsigned char> _bytes): bytes(_bytes) { }

const CBinary CBinary::getPart(size_t offset, size_t count) const
{
	if (offset == 0 && count == 0) {
		return *this;
	}

	if (offset >= bytes.size()) {
		throw std::out_of_range(strenc("Offset is out of the range of the data vector."));
	}

	if (count == 0 || offset + count > bytes.size()) {
		count = bytes.size() - offset;
	}

	auto subVector = std::vector<unsigned char>(&bytes[offset], &bytes[offset + count]);

	return CBinary(subVector);
}

const std::vector<unsigned char> CBinary::getBytes(size_t offset, size_t count) const {
	return getPart(offset, count).bytes;
}

const std::string CBinary::getBytesAsString(size_t offset, size_t count) const
{
	auto vec = getBytes(offset, count);
	
	return std::string(vec.begin(), vec.end());
}

const size_t CBinary::getSize() const
{
	return bytes.size();
}

const std::uintptr_t CBinary::getOffset(size_t offset) const
{
	if (offset >= bytes.size()) {
		throw std::out_of_range(strenc("Offset is out of the range of the data vector."));
	}

	return reinterpret_cast<std::uintptr_t>(&bytes[offset]);
}

