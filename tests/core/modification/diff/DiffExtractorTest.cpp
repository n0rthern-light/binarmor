#include "core/modification/diff/DiffExtractor.hpp"
#include "core/file/BinaryModification.hpp"
#include <gtest/gtest.h>

const auto bytes = byte_vec {0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A};

TEST(DiffExtractorTest, WillBeEmptyIfThereIsNoDiff)
{
    auto modified = byte_vec {0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A};

    auto diffs = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diffs.size(), 0);
}

TEST(DiffExtractorTest, CanDetectRemovalFromEnd)
{
    auto modified = byte_vec {0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00};

    auto diffs = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diffs.size(), 1);
    ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::REMOVE);
    ASSERT_EQ(diffs[0].offset, 10);
    ASSERT_EQ(diffs[0].size, 3);
}

TEST(DiffExtractorTest, CanDetectRemovalFromBegin)
{
    auto modified = byte_vec {0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A};

    auto diffs = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diffs.size(), 1);
    ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::REMOVE);
    ASSERT_EQ(diffs[0].offset, 0);
    ASSERT_EQ(diffs[0].size, 3);
}

TEST(DiffExtractorTest, CanDetectRemovalFromMiddle)
{
    auto modified = byte_vec {0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x0A};

    auto diffs = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diffs.size(), 1);
    ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::REMOVE);
    ASSERT_EQ(diffs[0].offset, 6);
    ASSERT_EQ(diffs[0].size, 3);
}

TEST(DiffExtractorTest, CanDetectAddFromEnd)
{
    auto modified = byte_vec {0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A, 0xCC, 0x01, 0x02};

    auto diffs = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diffs.size(), 1);
    ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::ADD);
    ASSERT_EQ(diffs[0].offset, 13);
    ASSERT_EQ(diffs[0].size, 3);
    ASSERT_EQ(diffs[0].newBytes, byte_vec({0xCC, 0x01, 0x02}));
}

TEST(DiffExtractorTest, CanDetectAddFromBegin)
{
    auto modified = byte_vec {0xCC, 0x01, 0x02, 0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A};

    auto diffs = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diffs.size(), 1);
    ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::ADD);
    ASSERT_EQ(diffs[0].offset, 0);
    ASSERT_EQ(diffs[0].size, 3);
    ASSERT_EQ(diffs[0].newBytes, byte_vec({0xCC, 0x01, 0x02}));
}

TEST(DiffExtractorTest, CanDetectAddFromMiddle)
{
    auto modified = byte_vec {0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0xCC, 0x01, 0x02, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A};

    auto diffs = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diffs.size(), 1);
    ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::ADD);
    ASSERT_EQ(diffs[0].offset, 6);
    ASSERT_EQ(diffs[0].size, 3);
    ASSERT_EQ(diffs[0].newBytes, byte_vec({0xCC, 0x01, 0x02}));
}

TEST(DiffExtractorTest, CanDetectModifyFromEnd)
{
    auto modified = byte_vec {0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFE, 0xFC, 0xA0};

    auto diffs = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diffs.size(), 1);
    ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::MODIFY);
    ASSERT_EQ(diffs[0].offset, 10);
    ASSERT_EQ(diffs[0].size, 3);
    ASSERT_EQ(diffs[0].oldBytes, byte_vec({0xFF, 0xFF, 0x0A}));
    ASSERT_EQ(diffs[0].newBytes, byte_vec({0xFE, 0xFC, 0xA0}));
}

TEST(DiffExtractorTest, CanDetectModifyFromBegin)
{
    auto modified = byte_vec {0xFE, 0xFC, 0xA0, 0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A};

    auto diffs = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diffs.size(), 1);
    ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::MODIFY);
    ASSERT_EQ(diffs[0].offset, 0);
    ASSERT_EQ(diffs[0].size, 3);
    ASSERT_EQ(diffs[0].oldBytes, byte_vec({0xAA, 0x90, 0xCC}));
    ASSERT_EQ(diffs[0].newBytes, byte_vec({0xFE, 0xFC, 0xA0}));
}

TEST(DiffExtractorTest, CanDetectModifyFromMiddle)
{
    auto modified = byte_vec {0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0xFE, 0xFC, 0xA0, 0x00, 0xFF, 0xFF, 0x0A};

    auto diffs = CDiffExtractor::extract(bytes, modified);

    ASSERT_EQ(diffs.size(), 1);
    ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::MODIFY);
    ASSERT_EQ(diffs[0].offset, 6);
    ASSERT_EQ(diffs[0].size, 3);
    ASSERT_EQ(diffs[0].oldBytes, byte_vec({0x0F, 0xBC, 0x01}));
    ASSERT_EQ(diffs[0].newBytes, byte_vec({0xFE, 0xFC, 0xA0}));
}

TEST(DiffExtractorTest, CanDetectMultipleChanges)
{
    {
        SCOPED_TRACE("REMOVAL_AND_MODIFICATION");

        auto modified = byte_vec {0xCC, 0x00, 0x00, 0x00, 0xFE, 0xFC, 0xA0, 0x00, 0xFF, 0xFF, 0x00};

        auto diffs = CDiffExtractor::extract(bytes, modified);

        ASSERT_EQ(diffs.size(), 4);

        ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::REMOVE);
        ASSERT_EQ(diffs[0].offset, 0);
        ASSERT_EQ(diffs[0].size, 2);
        ASSERT_EQ(diffs[0].oldBytes, byte_vec({0xAA, 0x90}));
        ASSERT_EQ(diffs[0].newBytes, byte_vec({}));

        ASSERT_EQ(diffs[1].type, BinaryModificationDiffType::MODIFY);
        ASSERT_EQ(diffs[1].offset, 4);
        ASSERT_EQ(diffs[1].size, 3);
        ASSERT_EQ(diffs[1].oldBytes, byte_vec({0x0F, 0xBC, 0x01}));
        ASSERT_EQ(diffs[1].newBytes, byte_vec({0xFE, 0xFC, 0xA0}));

        ASSERT_EQ(diffs[2].type, BinaryModificationDiffType::MODIFY);
        ASSERT_EQ(diffs[2].offset, 10);
        ASSERT_EQ(diffs[2].size, 1);
        ASSERT_EQ(diffs[2].oldBytes, byte_vec({0x0A}));
        ASSERT_EQ(diffs[2].newBytes, byte_vec({0x00}));
    }

    {
        SCOPED_TRACE("ADDITION_AND_MODIFICATION");

        auto modified = byte_vec {0xCC, 0x00, 0x00, 0x00, 0xFE, 0xFC, 0xA0, 0x00, 0xFF, 0xFF, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC};

        auto diffs = CDiffExtractor::extract(bytes, modified);

        ASSERT_EQ(diffs.size(), 2);

        ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::ADD);
        ASSERT_EQ(diffs[0].offset, 0);
        ASSERT_EQ(diffs[0].size, 16);
        ASSERT_EQ(diffs[0].oldBytes, byte_vec({}));
        ASSERT_EQ(diffs[0].newBytes, byte_vec({0xCC, 0x00, 0x00, 0x00, 0xFE, 0xFC, 0xA0, 0x00, 0xFF, 0xFF, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC}));

        ASSERT_EQ(diffs[1].type, BinaryModificationDiffType::REMOVE);
        ASSERT_EQ(diffs[1].offset, 16);
        ASSERT_EQ(diffs[1].size, 13);
        ASSERT_EQ(diffs[1].oldBytes, byte_vec({0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A}));
        ASSERT_EQ(diffs[1].newBytes, byte_vec());
    }

    {
        SCOPED_TRACE("MULTIPLE_ADDS");

        auto modified = byte_vec {0xAA, 0xCC, 0xCC, 0x90, 0xCC, 0x00, 0x00, 0xCC, 0xCC, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A, 0xCC};

        auto diffs = CDiffExtractor::extract(bytes, modified);

        ASSERT_EQ(diffs.size(), 3);

        ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::ADD);
        ASSERT_EQ(diffs[0].offset, 1);
        ASSERT_EQ(diffs[0].size, 2);
        ASSERT_EQ(diffs[0].oldBytes, byte_vec({}));
        ASSERT_EQ(diffs[0].newBytes, byte_vec({0xCC, 0xCC}));

        ASSERT_EQ(diffs[1].type, BinaryModificationDiffType::ADD);
        ASSERT_EQ(diffs[1].offset, 7);
        ASSERT_EQ(diffs[1].size, 2);
        ASSERT_EQ(diffs[1].oldBytes, byte_vec({}));
        ASSERT_EQ(diffs[1].newBytes, byte_vec({0xCC, 0xCC}));

        ASSERT_EQ(diffs[2].type, BinaryModificationDiffType::ADD);
        ASSERT_EQ(diffs[2].offset, 17);
        ASSERT_EQ(diffs[2].size, 1);
        ASSERT_EQ(diffs[2].oldBytes, byte_vec({}));
        ASSERT_EQ(diffs[2].newBytes, byte_vec({0xCC}));
    }

    {
        SCOPED_TRACE("MULTIPLE_REMOVALS");

        auto modified = byte_vec {0x90, 0xCC, 0x0F, 0xBC, 0x01, 0x00, 0xFF};

        auto diffs = CDiffExtractor::extract(bytes, modified);

        ASSERT_EQ(diffs.size(), 3);

        ASSERT_EQ(diffs[0].type, BinaryModificationDiffType::REMOVE);
        ASSERT_EQ(diffs[0].offset, 0);
        ASSERT_EQ(diffs[0].size, 1);
        ASSERT_EQ(diffs[0].oldBytes, byte_vec({0xAA}));
        ASSERT_EQ(diffs[0].newBytes, byte_vec({}));

        ASSERT_EQ(diffs[1].type, BinaryModificationDiffType::REMOVE);
        ASSERT_EQ(diffs[1].offset, 2);
        ASSERT_EQ(diffs[1].size, 3);
        ASSERT_EQ(diffs[1].oldBytes, byte_vec({0x00, 0x00, 0x00}));
        ASSERT_EQ(diffs[1].newBytes, byte_vec({}));

        ASSERT_EQ(diffs[2].type, BinaryModificationDiffType::REMOVE);
        ASSERT_EQ(diffs[2].offset, 7);
        ASSERT_EQ(diffs[2].size, 2);
        ASSERT_EQ(diffs[2].oldBytes, byte_vec({0xFF, 0x0A}));
        ASSERT_EQ(diffs[2].newBytes, byte_vec({}));
    }
}

