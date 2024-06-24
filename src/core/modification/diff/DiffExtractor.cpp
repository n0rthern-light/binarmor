#include "DiffExtractor.hpp"
#include "core/file/BinaryModification.hpp"
#include "shared/value/ByteVecOperations.hpp"

const vec_diff CDiffExtractor::extract(const byte_vec& original, const byte_vec& modified)
{
    std::vector<const BinaryModificationDiff_t> diffs;
    byte_vec tempOriginal = original;
    const auto modifiedSize = modified.size();

extract_start:
    if (tempOriginal.size() == modifiedSize) {
        size_t i = 0;
        while (i < modifiedSize) {
            if (tempOriginal[i] != modified[i]) {
                size_t start = i;
                byte_vec oldBytes;
                byte_vec newBytes;
                while (i < modifiedSize && tempOriginal[i] != modified[i]) {
                    oldBytes.push_back(tempOriginal[i]);
                    newBytes.push_back(modified[i]);
                    ++i;
                }
                
                tempOriginal = CByteVecOperations::bytesModify(tempOriginal, start, newBytes);
                diffs.push_back(BinaryModificationDiff_t::modify(start, oldBytes, newBytes));
            } else {
                ++i;
            }
        }
    } else if (tempOriginal.size() < modified.size()) {
        size_t i = 0;
        while (i < modified.size()) {
            if (tempOriginal[i] != modified[i]) {
                size_t start = i;
                byte_vec newBytes;
                while (i < modified.size() && tempOriginal[start] != modified[i]) {
                    newBytes.push_back(modified[i]);
                    ++i;
                }

                tempOriginal = CByteVecOperations::bytesInsert(tempOriginal, start, newBytes);
                diffs.push_back(BinaryModificationDiff_t::add(start, newBytes));
                goto extract_start;
            } else {
                ++i;
            }
        }
    } 
    else if (tempOriginal.size() > modifiedSize) {
        size_t i = 0;
        while (i < tempOriginal.size()) {
            if (tempOriginal[i] != modified[i]) {
                size_t start = i;
                byte_vec oldBytes;
                while (i < tempOriginal.size() && tempOriginal[i] != modified[start]) {
                    oldBytes.push_back(tempOriginal[i]);
                    ++i;
                }

                tempOriginal = CByteVecOperations::bytesRemove(tempOriginal, start, oldBytes.size());
                diffs.push_back(BinaryModificationDiff_t::remove(start, oldBytes));
                goto extract_start;
            } else {
                ++i;
            }
        }
    }

    return diffs;
}

