#include <gtest/gtest.h>
#include "shared/value/Unsigned.hpp"
#include <climits>
#include <limits>
#include <vector>

uint32_t maxUint32 = std::numeric_limits<uint_32>::max();
uint64_t maxUint64 = std::numeric_limits<uint_64>::max();

TEST(UnsignedTest, WorksWith32BitUnisgnedInts)
{
    std::vector<CUnsigned> vec {
        CUnsigned(0),
        CUnsigned(as_32(10)),
        CUnsigned(15),
        CUnsigned(maxUint32 - 1),
        CUnsigned(maxUint32),
    };

    {
        SCOPED_TRACE("Testing address type");

        for(auto v : vec) {
            ASSERT_EQ(v.bitType(), AddressType::_32_BIT);
        }
    }

    {
        SCOPED_TRACE("Testing reading address");

        ASSERT_EQ(vec[0].get(), as_32(0));
        ASSERT_EQ(vec[1].get(), as_32(10));
        ASSERT_EQ(vec[2].get(), as_32(15));
        ASSERT_EQ(vec[3].get(), as_32(4294967294));
        ASSERT_EQ(vec[4].get(), as_32(4294967295));
    }

    {
        SCOPED_TRACE("Testing reading as string");

        ASSERT_STREQ(vec[0].asDecimalString().c_str(), "0");
        ASSERT_STREQ(vec[0].asFullHexString().c_str(), "0x00000000");
        ASSERT_STREQ(vec[0].asShortHexString().c_str(), "0x0");

        ASSERT_STREQ(vec[1].asDecimalString().c_str(), "10");
        ASSERT_STREQ(vec[1].asFullHexString().c_str(), "0x0000000A");
        ASSERT_STREQ(vec[1].asShortHexString().c_str(), "0xA");

        ASSERT_STREQ(vec[2].asDecimalString().c_str(), "15");
        ASSERT_STREQ(vec[2].asFullHexString().c_str(), "0x0000000F");
        ASSERT_STREQ(vec[2].asShortHexString().c_str(), "0xF");

        ASSERT_STREQ(vec[3].asDecimalString().c_str(), "4294967294");
        ASSERT_STREQ(vec[3].asFullHexString().c_str(), "0xFFFFFFFE");
        ASSERT_STREQ(vec[3].asShortHexString().c_str(), "0xFFFFFFFE");

        ASSERT_STREQ(vec[4].asDecimalString().c_str(), "4294967295");
        ASSERT_STREQ(vec[4].asFullHexString().c_str(), "0xFFFFFFFF");
        ASSERT_STREQ(vec[4].asShortHexString().c_str(), "0xFFFFFFFF");
    }
}

TEST(UnsignedTest, WorksWith64BitUnisgnedInts)
{
    std::vector<CUnsigned> vec {
        CUnsigned(as_64(0)),
        CUnsigned(as_64(10)),
        CUnsigned(as_64(15)),
        CUnsigned(as_64(maxUint32 - 1)),
        CUnsigned(as_64(as_64(maxUint32) + 1)),
        CUnsigned(as_64(maxUint64 - 10000)),
        CUnsigned(as_64(maxUint64)),
    };

    {
        SCOPED_TRACE("Testing correct address type");

        for(auto v : vec) {
            ASSERT_EQ(v.bitType(), AddressType::_64_BIT);
        }
    }

    {
        SCOPED_TRACE("Testing reading address");

        ASSERT_EQ(vec[0].get(), as_64(0));
        ASSERT_EQ(vec[1].get(), as_64(10));
        ASSERT_EQ(vec[2].get(), as_64(15));
        ASSERT_EQ(vec[3].get(), as_64(4294967294));
        ASSERT_EQ(vec[4].get(), as_64(4294967296));
        ASSERT_EQ(vec[5].get(), as_64(18446744073709541615));
        ASSERT_EQ(vec[6].get(), as_64(18446744073709551615));
    }

    {
        SCOPED_TRACE("Testing reading as string");

        ASSERT_STREQ(vec[0].asDecimalString().c_str(), "0");
        ASSERT_STREQ(vec[0].asFullHexString().c_str(), "0x0000000000000000");
        ASSERT_STREQ(vec[0].asShortHexString().c_str(), "0x0");

        ASSERT_STREQ(vec[1].asDecimalString().c_str(), "10");
        ASSERT_STREQ(vec[1].asFullHexString().c_str(), "0x000000000000000A");
        ASSERT_STREQ(vec[1].asShortHexString().c_str(), "0xA");

        ASSERT_STREQ(vec[2].asDecimalString().c_str(), "15");
        ASSERT_STREQ(vec[2].asFullHexString().c_str(), "0x000000000000000F");
        ASSERT_STREQ(vec[2].asShortHexString().c_str(), "0xF");

        ASSERT_STREQ(vec[3].asDecimalString().c_str(), "4294967294");
        ASSERT_STREQ(vec[3].asFullHexString().c_str(), "0x00000000FFFFFFFE");
        ASSERT_STREQ(vec[3].asShortHexString().c_str(), "0xFFFFFFFE");

        ASSERT_STREQ(vec[4].asDecimalString().c_str(), "4294967296");
        ASSERT_STREQ(vec[4].asFullHexString().c_str(), "0x0000000100000000");
        ASSERT_STREQ(vec[4].asShortHexString().c_str(), "0x100000000");

        ASSERT_STREQ(vec[5].asDecimalString().c_str(), "18446744073709541615");
        ASSERT_STREQ(vec[5].asFullHexString().c_str(), "0xFFFFFFFFFFFFD8EF");
        ASSERT_STREQ(vec[5].asShortHexString().c_str(), "0xFFFFFFFFFFFFD8EF");

        ASSERT_STREQ(vec[6].asDecimalString().c_str(), "18446744073709551615");
        ASSERT_STREQ(vec[6].asFullHexString().c_str(), "0xFFFFFFFFFFFFFFFF");
        ASSERT_STREQ(vec[6].asShortHexString().c_str(), "0xFFFFFFFFFFFFFFFF");
    }
}

