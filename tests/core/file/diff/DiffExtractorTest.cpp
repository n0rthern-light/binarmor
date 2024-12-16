#include "core/file/diff/DiffExtractor.hpp"
#include "core/file/BinaryModification.hpp"
#include <gtest/gtest.h>

using namespace program::core::file::diff;
using namespace program::core::file;
using namespace program::shared::types;

const auto bytes = byte_vec {0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A};

TEST(DiffExtractorTest, WillBeEmptyIfThereIsNoDiff)
{
    auto modified = byte_vec {0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A};

    auto diff = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diff.size(), 0);
}

TEST(DiffExtractorTest, CanDetectRemoval)
{
    auto modified = byte_vec {};

    auto diff = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diff.size(), 1);
    ASSERT_EQ(diff[0].type, BinaryModificationDiffType::REMOVE);
    ASSERT_EQ(diff[0].oldBytes.size(), bytes.size());
}

TEST(DiffExtractorTest, CanDetectAdd)
{
    auto modified = byte_vec {0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A, 0x90, 0x90, 0x90};

    auto diff = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diff.size(), 1);
    ASSERT_EQ(diff[0].type, BinaryModificationDiffType::ADD);
    ASSERT_EQ(diff[0].newBytes, (byte_vec {0x90, 0x90, 0x90}));
}

