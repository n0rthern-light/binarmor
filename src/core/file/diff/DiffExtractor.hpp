#ifndef CORE_MODIFICATION_DIFF__DIFF_EXTRACTOR_HPP_
#define CORE_MODIFICATION_DIFF__DIFF_EXTRACTOR_HPP_

#include "core/file/BinaryModification.hpp"

namespace program::core::file::diff {
    class CDiffExtractor
    {
    public:
        static const vec_diff extract(const program::shared::types::byte_vec& original, const program::shared::types::byte_vec& modified);
    };
}

#endif // CORE_MODIFICATION_DIFF__DIFF_EXTRACTOR_HPP_
