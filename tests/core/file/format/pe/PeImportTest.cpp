#include <gtest/gtest.h>
#include "../../BinaryMother.hpp"
#include <stdio.h>

TEST(PeImportTest, X86ExeImportsAreCorrect)
{
    auto imports = BinaryMother::x86exe()->imports();
    ASSERT_EQ(imports.size(), 2);

    {
        SCOPED_TRACE("KERNEL32");

        auto kernel32 = imports.find("KERNEL32.dll");
        ASSERT_NE(kernel32, imports.end());

        auto kernel32Module = kernel32->second;

        ASSERT_STREQ(kernel32Module->name().c_str(), "KERNEL32.dll");
        ASSERT_EQ(kernel32Module->rva(), 0xC000);
        ASSERT_EQ(kernel32Module->size(), 0x14);
        ASSERT_EQ(kernel32Module->origin().offset(), 0x8A00);
        ASSERT_EQ(kernel32Module->imports().size(), 15);
    }

    {
        SCOPED_TRACE("msvcrt.dll");

        auto msvcrt = imports.find("msvcrt.dll");
        ASSERT_NE(msvcrt, imports.end());

        auto msvcrtModule = msvcrt->second;

        ASSERT_STREQ(msvcrtModule->name().c_str(), "msvcrt.dll");
        ASSERT_EQ(msvcrtModule->rva(), 0xC014);
        ASSERT_EQ(msvcrtModule->size(), 0x14);
        ASSERT_EQ(msvcrtModule->origin().offset(), 0x8A14);
        ASSERT_EQ(msvcrtModule->imports().size(), 35);
    }
}

TEST(PeImportTest, X86DllImportsAreCorrect)
{
    auto imports = BinaryMother::x86dll()->imports();
    ASSERT_EQ(imports.size(), 2);

    {
        SCOPED_TRACE("KERNEL32");

        auto kernel32 = imports.find("KERNEL32.dll");
        ASSERT_NE(kernel32, imports.end());

        auto kernel32Module = kernel32->second;

        ASSERT_STREQ(kernel32Module->name().c_str(), "KERNEL32.dll");
        ASSERT_EQ(kernel32Module->rva(), 0xD000);
        ASSERT_EQ(kernel32Module->size(), 0x14);
        ASSERT_EQ(kernel32Module->origin().offset(), 0x8800);
        ASSERT_EQ(kernel32Module->imports().size(), 14);
    }

    {
        SCOPED_TRACE("msvcrt.dll");

        auto msvcrt = imports.find("msvcrt.dll");
        ASSERT_NE(msvcrt, imports.end());

        auto msvcrtModule = msvcrt->second;

        ASSERT_STREQ(msvcrtModule->name().c_str(), "msvcrt.dll");
        ASSERT_EQ(msvcrtModule->rva(), 0xD014);
        ASSERT_EQ(msvcrtModule->size(), 0x14);
        ASSERT_EQ(msvcrtModule->origin().offset(), 0x8814);
        ASSERT_EQ(msvcrtModule->imports().size(), 25);
    }
}

TEST(PeImportTest, X86_64ExeImportsAreCorrect)
{
    auto imports = BinaryMother::x86_64exe()->imports();
    ASSERT_EQ(imports.size(), 2);

    {
        SCOPED_TRACE("KERNEL32");

        auto kernel32 = imports.find("KERNEL32.dll");
        ASSERT_NE(kernel32, imports.end());

        auto kernel32Module = kernel32->second;

        ASSERT_STREQ(kernel32Module->name().c_str(), "KERNEL32.dll");
        ASSERT_EQ(kernel32Module->rva(), 0xE000);
        ASSERT_EQ(kernel32Module->size(), 0x14);
        ASSERT_EQ(kernel32Module->origin().offset(), 0x9400);
        ASSERT_EQ(kernel32Module->imports().size(), 13);
    }

    {
        SCOPED_TRACE("msvcrt.dll");

        auto msvcrt = imports.find("msvcrt.dll");
        ASSERT_NE(msvcrt, imports.end());

        auto msvcrtModule = msvcrt->second;

        ASSERT_STREQ(msvcrtModule->name().c_str(), "msvcrt.dll");
        ASSERT_EQ(msvcrtModule->rva(), 0xE014);
        ASSERT_EQ(msvcrtModule->size(), 0x14);
        ASSERT_EQ(msvcrtModule->origin().offset(), 0x9414);
        ASSERT_EQ(msvcrtModule->imports().size(), 34);
    }
}

TEST(PeImportTest, X86_64DllImportsAreCorrect)
{
    auto imports = BinaryMother::x86_64dll()->imports();
    ASSERT_EQ(imports.size(), 2);

    {
        SCOPED_TRACE("KERNEL32");

        auto kernel32 = imports.find("KERNEL32.dll");
        ASSERT_NE(kernel32, imports.end());

        auto kernel32Module = kernel32->second;

        ASSERT_STREQ(kernel32Module->name().c_str(), "KERNEL32.dll");
        ASSERT_EQ(kernel32Module->rva(), 0xE000);
        ASSERT_EQ(kernel32Module->size(), 0x14);
        ASSERT_EQ(kernel32Module->origin().offset(), 0x9000);
        ASSERT_EQ(kernel32Module->imports().size(), 12);
    }

    {
        SCOPED_TRACE("msvcrt.dll");

        auto msvcrt = imports.find("msvcrt.dll");
        ASSERT_NE(msvcrt, imports.end());

        auto msvcrtModule = msvcrt->second;

        ASSERT_STREQ(msvcrtModule->name().c_str(), "msvcrt.dll");
        ASSERT_EQ(msvcrtModule->rva(), 0xE014);
        ASSERT_EQ(msvcrtModule->size(), 0x14);
        ASSERT_EQ(msvcrtModule->origin().offset(), 0x9014);
        ASSERT_EQ(msvcrtModule->imports().size(), 23);
    }
}

