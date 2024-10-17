#ifndef SHARED_DIFF_DIFF_MATCH_PATCH_HPP_
#define SHARED_DIFF_DIFF_MATCH_PATCH_HPP_

#include "../types/defines.hpp"
#include <optional>

namespace diff
{
    enum class EditType { None, Insert, Delete };

    struct Diff {
        EditType type;
        program::shared::types::binary_offset index;
        program::shared::types::byte_vec values;

        Diff(EditType t, size_t i, const program::shared::types::byte_vec &v) : type(t), index(i), values(v) {}
    };

    std::vector<Diff> match(const program::shared::types::byte_vec &original, const program::shared::types::byte_vec &target, std::optional<program::shared::types::binary_offset> offset = std::nullopt);
    program::shared::types::byte_vec patch(const program::shared::types::byte_vec &original, const std::vector<Diff> &diffs);
};

#endif // SHARED_DIFF_DIFF_MATCH_PATCH_HPP_
