#include <gtest/gtest.h>
#include <core/file/BinaryFile.hpp>

auto bytes = std::vector<unsigned char> {0xAA, 0xCC, 0x90};
std::string path = "C:\\System32\\ntdll.dll";

CBinaryFile* fresh()
{
    return new CBinaryFile(path, CBinary(bytes));
}

TEST(BinaryFileTest, IsBeingSetUpCorrectly)
{
    auto binaryFile = fresh();

    ASSERT_STREQ(binaryFile->filePath().c_str(), path.c_str());
    ASSERT_EQ(binaryFile->binary(), CBinary(bytes));
    ASSERT_EQ(binaryFile->hasFormatRecognized(), false);
    ASSERT_EQ(binaryFile->hasFlags(BinaryFileFlags::Analyzed), false);
}

TEST(BinaryFileTest, FlagsCanBeToggled)
{
    auto binaryFile = fresh();

    ASSERT_EQ(binaryFile->hasFlags(BinaryFileFlags::None), true);
    ASSERT_EQ(binaryFile->hasFlags(BinaryFileFlags::Analyzed), false);
    ASSERT_EQ(binaryFile->hasAnyFlags(), false);

    binaryFile->enableFlags(BinaryFileFlags::Analyzed);

    ASSERT_EQ(binaryFile->hasFlags(BinaryFileFlags::None), false);
    ASSERT_EQ(binaryFile->hasFlags(BinaryFileFlags::Analyzed), true);
    ASSERT_EQ(binaryFile->hasAnyFlags(), true);

    binaryFile->disableFlags(BinaryFileFlags::Analyzed);

    ASSERT_EQ(binaryFile->hasFlags(BinaryFileFlags::None), true);
    ASSERT_EQ(binaryFile->hasFlags(BinaryFileFlags::Analyzed), false);
    ASSERT_EQ(binaryFile->hasAnyFlags(), false);
}

