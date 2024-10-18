#include "diff_match_patch.hpp"
#include <optional>

using namespace program::shared::types;
using namespace program::shared::diff;

std::vector<Diff> program::shared::diff::match(const byte_vec &original, const byte_vec &target, std::optional<binary_offset> offset) {
    std::vector<Diff> diffs;
    binary_offset i = 0, j = 0;
    binary_offset offsetAddy = offset.has_value() ? offset.value() : 0;

    while (i < original.size() && j < target.size()) {
        if (original[i] == target[j]) {
            ++i;
            ++j;
        } else {
            size_t oi = i, tj = j;
            while (i < original.size() && j < target.size() && original[i] != target[j]) {
                ++i;
                ++j;
            }

            if (oi < i) {
                diffs.emplace_back(EditType::Delete, oi + offsetAddy, byte_vec(original.begin() + oi, original.begin() + i));
            }
            if (tj < j) {
                diffs.emplace_back(EditType::Insert, tj + offsetAddy, byte_vec(target.begin() + tj, target.begin() + j));
            }
        }
    }

    if (i < original.size()) {
        diffs.emplace_back(EditType::Delete, i + offsetAddy, byte_vec(original.begin() + i, original.end()));
    }
    if (j < target.size()) {
        diffs.emplace_back(EditType::Insert, i + offsetAddy, byte_vec(target.begin() + j, target.end()));
    }

    return diffs;
}

byte_vec program::shared::diff::patch(const byte_vec &original, const std::vector<Diff> &diffs) {
    byte_vec result = { };
    binary_offset currentIndex = 0;

    for (const auto &diff : diffs) {
        if (currentIndex < diff.index) {
            result.insert(result.end(), original.begin() + currentIndex, original.begin() + diff.index);
            currentIndex = diff.index;
        }

        if (diff.type == EditType::Delete) {
            currentIndex += diff.values.size();
        } else if (diff.type == EditType::Insert) {
            result.insert(result.end(), diff.values.begin(), diff.values.end());
        }
    }

    if (currentIndex < original.size()) {
        result.insert(result.end(), original.begin() + currentIndex, original.end());
    }

    return result;
}
