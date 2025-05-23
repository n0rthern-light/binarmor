#include <gtest/gtest.h>
#include "shared/value/Uuid.hpp"

TEST(UuidTest, CanGenerateUuid)
{
    auto uuid = new CUuid();
    ASSERT_TRUE(CUuid::isValidUuid(uuid->toString()));
}

TEST(UuidTest, CanCreateUuidFromString)
{
    auto uuid = new CUuid("65bb15c3-78f0-43b1-9be3-9258ffa561e8");
    ASSERT_TRUE(CUuid::isValidUuid(uuid->toString()));
}

TEST(UuidTest, RecognizesInvalidUuid)
{
    ASSERT_FALSE(CUuid::isValidUuid("invalid-uuid"));
}

TEST(UuidTest, CanGenerateUuidFromSeed)
{
    auto uuid1 = new CUuid("This is potentially a really good seed 12345 !@#$%$_ ,./';");
    auto uuid2 = new CUuid("This is potentially a really good seed 12345 !@#$%$_ ,./';");
    auto uuid3 = new CUuid("Different ID");
    ASSERT_TRUE(CUuid::isValidUuid(uuid1->toString()));
    ASSERT_TRUE(CUuid::isValidUuid(uuid2->toString()));
    ASSERT_TRUE(CUuid::isValidUuid(uuid3->toString()));
    ASSERT_STREQ(uuid1->toString().c_str(), uuid2->toString().c_str());
    ASSERT_STRNE(uuid1->toString().c_str(), uuid3->toString().c_str());
    ASSERT_STRNE(uuid2->toString().c_str(), uuid3->toString().c_str());
}

