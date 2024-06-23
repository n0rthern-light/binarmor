#pragma once

#include "core/file/BinaryModification.hpp"

class CDiffExtractor
{
public:
    const std::vector<const BinaryModificationDiff_t> extract(const byte_vec& original, const byte_vec& modified);
};
