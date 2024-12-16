#include "shared/value/ByteVecOperations.hpp"
#include <gtest/gtest.h>
#include "shared/types/defines.hpp"

using namespace program::shared::types;
using namespace program::shared::value;

TEST(CByteVecOperationsTest, AssertWithinRangeThrowsOutOfRange) {
    byte_vec vec = {0xAA, 0xBB, 0xCC};
    EXPECT_THROW(CByteVecOperations::assertWithinRange(vec, 3), std::out_of_range);
    EXPECT_NO_THROW(CByteVecOperations::assertWithinRange(vec, 2));
}

TEST(CByteVecOperationsTest, AssertWithinRangeWithRequiredSpaceThrowsOutOfRange) {
    byte_vec vec = {0xAA, 0xBB, 0xCC};
    EXPECT_THROW(CByteVecOperations::assertWithinRange(vec, 2, 2), std::out_of_range);
    EXPECT_NO_THROW(CByteVecOperations::assertWithinRange(vec, 1, 2));
}

TEST(CByteVecOperationsTest, BytesModifySuccess) {
    byte_vec vec = {0xAA, 0xBB, 0xCC};
    byte_vec other = {0x11, 0x22};
    byte_vec expected = {0xAA, 0x11, 0x22};
    EXPECT_EQ(CByteVecOperations::bytesModify(vec, 1, other), expected);
}

TEST(CByteVecOperationsTest, BytesModifyThrowsOutOfRange) {
    byte_vec vec = {0xAA, 0xBB, 0xCC};
    byte_vec other = {0x11, 0x22, 0x33, 0x44};
    EXPECT_THROW(CByteVecOperations::bytesModify(vec, 2, other), std::out_of_range);
}

TEST(CByteVecOperationsTest, BytesInsertSuccessWithNoGapFill) {
    byte_vec vec = {0xAA, 0xBB, 0xCC};
    byte_vec other = {0x11, 0x22};
    byte_vec expected = {0xAA, 0x11, 0x22, 0xBB, 0xCC};
    EXPECT_EQ(CByteVecOperations::bytesInsert(vec, 1, other), expected);
}

TEST(CByteVecOperationsTest, BytesInsertSuccessWithGapFill) {
    byte_vec vec = {0xAA, 0xBB, 0xCC};
    byte_vec other = {0x11, 0x22};
    byte_vec expected = {0xAA, 0xBB, 0xCC, 0x00, 0x00, 0x11, 0x22};
    EXPECT_EQ(CByteVecOperations::bytesInsert(vec, 5, other, 0x00), expected);
}

TEST(CByteVecOperationsTest, BytesInsertThrowsOutOfRangeWithoutGapFill) {
    byte_vec vec = {0xAA, 0xBB, 0xCC};
    byte_vec other = {0x11, 0x22};
    EXPECT_THROW(CByteVecOperations::bytesInsert(vec, 5, other), std::out_of_range);
}

TEST(CByteVecOperationsTest, BytesRemoveSuccess) {
    byte_vec vec = {0xAA, 0xBB, 0xCC};
    byte_vec expected = {0xAA};
    EXPECT_EQ(CByteVecOperations::bytesRemove(vec, 1, 2), expected);
}

TEST(CByteVecOperationsTest, BytesRemoveThrowsOutOfRange) {
    byte_vec vec = {0xAA, 0xBB, 0xCC};
    EXPECT_THROW(CByteVecOperations::bytesRemove(vec, 1, 3), std::out_of_range);
}

