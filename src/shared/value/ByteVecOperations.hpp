#pragma once

#include "../types/defines.hpp"
#include "../self_obfuscation/strenc.hpp"
#include <algorithm>
#include <optional>
#include <stdexcept>
#include <vector>

class CByteVecOperations
{
public:
    static void assertWithinRange(const byte_vec& byteVec, binary_offset offset, std::optional<binary_offset> requiredSpace = std::nullopt)
    {
        if (offset >= byteVec.size()) {
            throw std::out_of_range(strenc("Given offset is out off range"));
        }

        if (requiredSpace.has_value()) {
            assertWithinRange(byteVec, std::max(offset, offset + requiredSpace.value() - 1));
        }
    }

    static byte_vec bytesModify(byte_vec byteVec, binary_offset offset, const byte_vec& other)
    {
        assertWithinRange(byteVec, offset, std::optional<binary_offset>(other.size()));
        std::copy(other.begin(), other.end(), byteVec.begin() + offset);

        return byteVec;
    }

    static byte_vec bytesInsert(byte_vec byteVec, binary_offset offset, const byte_vec& other, std::optional<unsigned char> gapFillByte = std::nullopt)
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

    static byte_vec bytesRemove(byte_vec byteVec, binary_offset offset, binary_offset removeCount)
    {
        assertWithinRange(byteVec, offset, std::optional<binary_offset>(removeCount));
        byteVec.erase(byteVec.begin() + offset, byteVec.begin() + offset + removeCount);

        return byteVec;
    }
};
