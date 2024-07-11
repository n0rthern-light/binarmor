#ifndef CORE_MODIFICATION_DIFF__DIFF_EXTRACTOR_HPP_
#define CORE_MODIFICATION_DIFF__DIFF_EXTRACTOR_HPP_

#include "core/file/BinaryModification.hpp"

class CDiffExtractor
{
public:
    static const vec_diff extract(const byte_vec& original, const byte_vec& modified);
};

#endif // CORE_MODIFICATION_DIFF__DIFF_EXTRACTOR_HPP_
