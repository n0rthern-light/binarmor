#pragma once

#include "core/file/BinaryModification.hpp"

class CDiffExtractor
{
public:
    static const vec_diff extract(const byte_vec& original, const byte_vec& modified);
};
