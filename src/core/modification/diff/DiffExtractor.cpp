#include "DiffExtractor.hpp"
#include "core/file/BinaryModification.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include <algorithm>
#include <map>
#include <stdexcept>
#include <utility>

// based on myers diff algorithm

enum class EditType { None, Insert, Delete };

struct Diff {
    EditType type;
    unsigned int index;
    unsigned char value;
};

int min3(unsigned int a, unsigned int b, unsigned int c) {
    return std::min(std::min(a, b), c);
}

std::vector<Diff> myersDiff(const byte_vec& a, const byte_vec& b)
{
    unsigned int n = a.size();
    unsigned int m = b.size();
    std::vector<std::vector<unsigned int>> dp(n + 1, std::vector<unsigned int>(m + 1, 0));

    for (unsigned int i = 0; i <= n; ++i) dp[i][0] = i;

    for (unsigned int j = 0; j <= m; ++j) dp[0][j] = j;

    for (unsigned int i = 1; i <= n; ++i) {
        #pragma omp parallel for
        for (unsigned int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min3(dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1);
            }
        }
    }

    std::vector<Diff> diffs;
    unsigned int i = n, j = m;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && a[i - 1] == b[j - 1]) {
            diffs.push_back({EditType::None, i - 1, a[i - 1]});
            --i;
            --j;
        } else if (i > 0 && (j == 0 || dp[i][j] == dp[i - 1][j] + 1)) {
            diffs.push_back({EditType::Delete, i - 1, a[i - 1]});
            --i;
        } else if (j > 0 && (i == 0 || dp[i][j] == dp[i][j - 1] + 1)) {
            diffs.push_back({EditType::Insert, j - 1, b[j - 1]});
            --j;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            diffs.push_back({EditType::Delete, i - 1, a[i - 1]});
            diffs.push_back({EditType::Insert, j - 1, b[j - 1]});
            --i;
            --j;
        }
    }

    std::reverse(diffs.begin(), diffs.end());
    return diffs;
}

const vec_diff CDiffExtractor::extract(const byte_vec& original, const byte_vec& modified)
{
    std::vector<const BinaryModificationDiff_t> diffs;

    const auto myersDiffBytes = myersDiff(original, modified);
    const auto myersDiffBytesSize = myersDiffBytes.size();

    auto indexedDiffs = std::map<binary_offset, std::pair<const Diff*, const Diff*>> { };
    
    for(auto i = 0; i < myersDiffBytesSize; ++i)
    {
        if (myersDiffBytes[i].type == EditType::None) {
            continue;
        }

        if (myersDiffBytes[i].type == EditType::Insert) {
            indexedDiffs[myersDiffBytes[i].index].first = &myersDiffBytes[i];
        } else if (myersDiffBytes[i].type == EditType::Delete) {
            indexedDiffs[myersDiffBytes[i].index].second = &myersDiffBytes[i];
        } else {
            throw std::logic_error(strenc("Unexpected behaviour"));
        }
    }

    for (auto it = indexedDiffs.begin(); it != indexedDiffs.end(); ++it)
    {
        const auto& currentPair = it->second;

        if (currentPair.first == nullptr && currentPair.second == nullptr) {
            throw std::logic_error(strenc("Invalid index pair"));
        }

        const auto& offset = it->first;
        auto oldBytes = byte_vec { };
        auto newBytes = byte_vec { };
        BinaryModificationDiffType type;

        while (
            it != indexedDiffs.end() &&
            !!currentPair.first == !!it->second.first &&
            !!currentPair.second == !!it->second.second
        ) {
            const auto& currentAdd = it->second.first;
            const auto& currentRemove = it->second.second;

            if (currentAdd != nullptr && currentRemove != nullptr) {
                type = BinaryModificationDiffType::MODIFY;
                oldBytes.push_back(currentRemove->value);
                newBytes.push_back(currentAdd->value);
            } else if (currentAdd != nullptr) {
                type = BinaryModificationDiffType::ADD;
                newBytes.push_back(currentAdd->value);
            } else if (currentRemove != nullptr) {
                type = BinaryModificationDiffType::REMOVE;
                oldBytes.push_back(currentRemove->value);
            } else {
                throw std::logic_error(strenc("Invalid index pair"));
            }

            ++it;
        }

        if (type == BinaryModificationDiffType::MODIFY) {
            diffs.push_back(BinaryModificationDiff_t::modify(offset, oldBytes, newBytes));
        } else if (type == BinaryModificationDiffType::ADD) {
            diffs.push_back(BinaryModificationDiff_t::add(offset, newBytes));
        } else if (type == BinaryModificationDiffType::REMOVE) {
            diffs.push_back(BinaryModificationDiff_t::remove(offset, oldBytes));
        } else {
            throw std::logic_error(strenc("Unsupported diff type"));
        }

        if (it == indexedDiffs.end()) {
            break;
        }
    }

    return diffs;
}

