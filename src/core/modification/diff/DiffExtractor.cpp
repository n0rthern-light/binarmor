#include "DiffExtractor.hpp"
#include "core/file/BinaryModification.hpp"
#include "shared/diff/diff_match_patch.hpp"
#include "shared/types/defines.hpp"
#include "shared/value/ByteVecOperations.hpp"

const vec_diff CDiffExtractor::extract(const byte_vec& original, const byte_vec& modified) {
    constexpr binary_offset CHUNK_SIZE = 1000;
    std::vector<const BinaryModificationDiff_t> diffs;

    const auto originalChunks = CByteVecOperations::chunk(original, CHUNK_SIZE);
    const auto modifiedChunks = CByteVecOperations::chunk(modified, CHUNK_SIZE);
    const auto originalChunksSize = originalChunks.size();
    const auto modifiedChunksSize = modifiedChunks.size();
    const auto biggestChunkSize = originalChunksSize > modifiedChunksSize ? originalChunksSize : modifiedChunksSize;

    for(binary_offset i = 0; i < biggestChunkSize; ++i) {
        const auto currentOffset = i * CHUNK_SIZE;
        const auto currentOriginalChunk = i < originalChunksSize ? originalChunks[i] : byte_vec { };
        const auto currentModifiedChunk = i < modifiedChunksSize ? modifiedChunks[i] : byte_vec { };

        const auto diff = diff::match(currentOriginalChunk, currentModifiedChunk, currentOffset);

        for(const auto& singleDiffSegment : diff) {
            if (singleDiffSegment.type == diff::EditType::Insert) {
                diffs.push_back(BinaryModificationDiff_t::add(singleDiffSegment.index, singleDiffSegment.values));
            } else if (singleDiffSegment.type == diff::EditType::Delete) {
                diffs.push_back(BinaryModificationDiff_t::remove(singleDiffSegment.index, singleDiffSegment.values));
            }
        }
    }

    return diffs;
}

