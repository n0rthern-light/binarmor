#ifndef SHARED_VALUE__BYTE_VEC_OPERATIONS_HPP_
#define SHARED_VALUE__BYTE_VEC_OPERATIONS_HPP_

#include "../types/defines.hpp"
#include "../self_obfuscation/strenc.hpp"
#include <algorithm>
#include <optional>
#include <stdexcept>
#include <vector>

namespace program::shared::value
{
    class CByteVecOperations
    {
    public:
        static void assertWithinRange(const types::byte_vec& byteVec, types::binary_offset offset, std::optional<types::binary_offset> requiredSpace = std::nullopt)
        {
            if (offset >= byteVec.size()) {
                throw std::out_of_range(strenc("Given offset is out off range"));
            }

            if (requiredSpace.has_value()) {
                assertWithinRange(byteVec, std::max(offset, offset + requiredSpace.value() - 1));
            }
        }

        static types::byte_vec bytesModify(types::byte_vec byteVec, types::binary_offset offset, const types::byte_vec& other)
        {
            assertWithinRange(byteVec, offset, std::optional<types::binary_offset>(other.size()));
            std::copy(other.begin(), other.end(), byteVec.begin() + offset);

            return byteVec;
        }

        static types::byte_vec bytesInsert(types::byte_vec byteVec, types::binary_offset offset, const types::byte_vec& other, std::optional<types::byte> gapFillByte = std::nullopt)
        {
            if (offset > byteVec.size()) {
                if (gapFillByte.has_value()) {
                    byteVec.resize(offset, gapFillByte.value());
                } else {
                    throw std::out_of_range(strenc("There would be an unexpected gap that must have specified fill byte before insertion"));
                }
            }
            byteVec.insert(byteVec.begin() + offset, other.begin(), other.end());

            return byteVec;
        }

        static types::byte_vec bytesAppendToEnd(const types::byte_vec& byteVec, const types::byte_vec& other)
        {
            return bytesInsert(byteVec, byteVec.size(), other);
        }

        static types::byte_vec bytesRemove(types::byte_vec byteVec, types::binary_offset offset, types::binary_offset removeCount)
        {
            assertWithinRange(byteVec, offset, std::optional<types::binary_offset>(removeCount));
            byteVec.erase(byteVec.begin() + offset, byteVec.begin() + offset + removeCount);

            return byteVec;
        }

        static std::vector<types::byte_vec> chunk(const types::byte_vec& byteVec, types::binary_offset chunkSize)
        {
            std::vector<types::byte_vec> chunks { };

            for (size_t i = 0; i < byteVec.size(); i += chunkSize) {
            types::byte_vec chunk(byteVec.begin() + i, byteVec.begin() + std::min(byteVec.size(), i + chunkSize));

                chunks.push_back(chunk);
            }

            return chunks;
        }
    };
}

#endif // SHARED_VALUE__BYTE_VEC_OPERATIONS_HPP_
