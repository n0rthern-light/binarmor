#include <gtest/gtest.h>
#include "../../BinaryMother.hpp"
#include <vector>
#include <stdio.h>

auto x86exe_Imports = BinaryMother::x86exe()->imports();
//auto x86dll_Imports = BinaryMother::x86dll()->imports();
//auto x86_64exe_Imports = BinaryMother::x86_64exe()->imports();
//auto x86_64dll_Imports = BinaryMother::x86_64dll()->imports();

TEST(PeImportTest, X86ExeImportsAreCorrect)
{
    //ASSERT_EQ(x86exe_Imports.size(), 35);
}

TEST(PeImportTest, X86DllImportsAreCorrect)
{
    //ASSERT_EQ(x86dll_Imports.size(), 35);
}

TEST(PeImportTest, X86_64ExeImportsAreCorrect)
{
    //ASSERT_EQ(x86_64exe_Imports.size(), 35);
}

TEST(PeImportTest, X86_64DllImportsAreCorrect)
{
    //ASSERT_EQ(x86_64dll_Imports.size(), 35);
}

