#include "core/file/Binary.hpp"
#include <gtest/gtest.h>
#include <core/file/BinaryFile.hpp>

const byteVector_t bytes = {0xAA, 0x90, 0xCC, 0x00, 0x00, 0x00, 0x0F, 0xBC, 0x01, 0x00, 0xFF, 0xFF, 0x0A};
const byteVector_t strBytes = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};

CBinary* fresh()
{
    return new CBinary(bytes);
}

TEST(BinaryFileTest, EqOperandWorks)
{
    auto first = *fresh();
    auto second = *fresh();

    ASSERT_TRUE(first == second);
}

TEST(BinaryFileTest, CanBePartitioned)
{
    auto binary = *fresh();

    ASSERT_EQ(binary.part(), binary);
    ASSERT_EQ(binary.part(0, 1), CBinary(byteVector_t {0xAA}));
    ASSERT_EQ(binary.part(binary.size() - 1, 1), CBinary(byteVector_t {0x0A}));
    ASSERT_EQ(binary.part(binary.size() - 4), CBinary(byteVector_t {0x00, 0xFF, 0xFF, 0x0A}));
    ASSERT_EQ(binary.part(0, 4), CBinary(byteVector_t {0xAA, 0x90, 0xCC, 0x00}));
    ASSERT_EQ(binary.part(4, 4), CBinary(byteVector_t {0x00, 0x00, 0x0F, 0xBC}));
}

TEST(BinaryFileTest, BytesCanBeCastedToString)
{
    auto bytes = new CBinary(strBytes);

    ASSERT_STREQ(bytes->bytesAsString().c_str(), "\xAA\x90\xCC");
}

