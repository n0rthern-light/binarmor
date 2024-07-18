#include <gtest/gtest.h>
#include "../BinaryMother.hpp"
#include <stdio.h>

const auto x86exe = BinaryMother::x86exe();

TEST(AddSectionHandlerTest, CanAddSection)
{
    // given
    const auto source = x86exe->binary().bytes();
}

