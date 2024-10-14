#include "DiffExtractor.hpp"
#include "core/file/BinaryModification.hpp"
#include "shared/diff/diff_match_patch.hpp"
#include "shared/types/defines.hpp"

using namespace program::core::file::diff;

const vec_diff CDiffExtractor::extract(const byte_vec& original, const byte_vec& modified) {
    std::vector<const BinaryModificationDiff_t> diffs;
    const auto diff = ::diff::match(original, modified);

    for(const auto& singleDiffSegment : diff) {
        if (singleDiffSegment.type == ::diff::EditType::Insert) {
            diffs.push_back(BinaryModificationDiff_t::add(singleDiffSegment.index, singleDiffSegment.values));
        } else if (singleDiffSegment.type == ::diff::EditType::Delete) {
            diffs.push_back(BinaryModificationDiff_t::remove(singleDiffSegment.index, singleDiffSegment.values));
        }
    }

    return diffs;
}

