#ifndef SHARED_DIFF_DIFF_MATCH_PATCH_HPP_
#define SHARED_DIFF_DIFF_MATCH_PATCH_HPP_

#include "../types/defines.hpp"
#include <optional>

namespace diff
{
    enum class EditType { None, Insert, Delete };

    struct Diff {
        EditType type;
        binary_offset index;
        byte_vec values;

        Diff(EditType t, size_t i, const byte_vec &v) : type(t), index(i), values(v) {}
    };

    std::vector<Diff> match(const byte_vec &original, const byte_vec &target, std::optional<binary_offset> offset = std::nullopt);
    byte_vec patch(const byte_vec &original, const std::vector<Diff> &diffs);
};

#endif // SHARED_DIFF_DIFF_MATCH_PATCH_HPP_
