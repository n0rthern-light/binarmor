#include <gtest/gtest.h>
#include "shared/value/AddressValue.hpp"
#include <climits>
#include <cstdint>
#include <limits>
#include <vector>
#include <stdio.h>

uint32_t maxUint32 = std::numeric_limits<uint32_t>::max();
uint64_t maxUint64 = std::numeric_limits<uint64_t>::max();

TEST(AddressValueTest, WorksWith32BitUnisgnedInts)
{
    std::vector<CAddressValue> vec {
        CAddressValue(0),
        CAddressValue(as32(10)),
        CAddressValue(15),
        CAddressValue(maxUint32 - 1),
        CAddressValue(maxUint32),
    };

    {
        SCOPED_TRACE("Testing address type");

        for(auto v : vec) {
            ASSERT_EQ(v.getType(), AddressType::_32_BIT);
        }
    }

    {
        SCOPED_TRACE("Testing reading address");

        ASSERT_EQ(vec[0].getAddress(), as32(0));
        ASSERT_EQ(vec[1].getAddress(), as32(10));
        ASSERT_EQ(vec[2].getAddress(), as32(15));
        ASSERT_EQ(vec[3].getAddress(), as32(4294967294));
        ASSERT_EQ(vec[4].getAddress(), as32(4294967295));
    }

    {
        SCOPED_TRACE("Testing reading as string");

        ASSERT_STREQ(vec[0].getAddressAsDecimalString().c_str(), "0");
        ASSERT_STREQ(vec[0].getAddressAsFullHexString().c_str(), "0x00000000");
        ASSERT_STREQ(vec[0].getAddressAsShortHexString().c_str(), "0x0");

        ASSERT_STREQ(vec[1].getAddressAsDecimalString().c_str(), "10");
        ASSERT_STREQ(vec[1].getAddressAsFullHexString().c_str(), "0x0000000A");
        ASSERT_STREQ(vec[1].getAddressAsShortHexString().c_str(), "0xA");

        ASSERT_STREQ(vec[2].getAddressAsDecimalString().c_str(), "15");
        ASSERT_STREQ(vec[2].getAddressAsFullHexString().c_str(), "0x0000000F");
        ASSERT_STREQ(vec[2].getAddressAsShortHexString().c_str(), "0xF");

        ASSERT_STREQ(vec[3].getAddressAsDecimalString().c_str(), "4294967294");
        ASSERT_STREQ(vec[3].getAddressAsFullHexString().c_str(), "0xFFFFFFFE");
        ASSERT_STREQ(vec[3].getAddressAsShortHexString().c_str(), "0xFFFFFFFE");

        ASSERT_STREQ(vec[4].getAddressAsDecimalString().c_str(), "4294967295");
        ASSERT_STREQ(vec[4].getAddressAsFullHexString().c_str(), "0xFFFFFFFF");
        ASSERT_STREQ(vec[4].getAddressAsShortHexString().c_str(), "0xFFFFFFFF");
    }
}

TEST(AddressValueTest, WorksWith64BitUnisgnedInts)
{
    std::vector<CAddressValue> vec {
        CAddressValue(as64(0)),
        CAddressValue(as64(10)),
        CAddressValue(as64(15)),
        CAddressValue(as64(maxUint32 - 1)),
        CAddressValue(as64(as64(maxUint32) + 1)),
        CAddressValue(as64(maxUint64 - 10000)),
        CAddressValue(as64(maxUint64)),
    };

    {
        SCOPED_TRACE("Testing correct address type");

        for(auto v : vec) {
            ASSERT_EQ(v.getType(), AddressType::_64_BIT);
        }
    }

    {
        SCOPED_TRACE("Testing reading address");

        ASSERT_EQ(vec[0].getAddress(), as64(0));
        ASSERT_EQ(vec[1].getAddress(), as64(10));
        ASSERT_EQ(vec[2].getAddress(), as64(15));
        ASSERT_EQ(vec[3].getAddress(), as64(4294967294));
        ASSERT_EQ(vec[4].getAddress(), as64(4294967296));
        ASSERT_EQ(vec[5].getAddress(), as64(18446744073709541615));
        ASSERT_EQ(vec[6].getAddress(), as64(18446744073709551615));
    }

    {
        SCOPED_TRACE("Testing reading as string");

        ASSERT_STREQ(vec[0].getAddressAsDecimalString().c_str(), "0");
        ASSERT_STREQ(vec[0].getAddressAsFullHexString().c_str(), "0x0000000000000000");
        ASSERT_STREQ(vec[0].getAddressAsShortHexString().c_str(), "0x0");

        ASSERT_STREQ(vec[1].getAddressAsDecimalString().c_str(), "10");
        ASSERT_STREQ(vec[1].getAddressAsFullHexString().c_str(), "0x000000000000000A");
        ASSERT_STREQ(vec[1].getAddressAsShortHexString().c_str(), "0xA");

        ASSERT_STREQ(vec[2].getAddressAsDecimalString().c_str(), "15");
        ASSERT_STREQ(vec[2].getAddressAsFullHexString().c_str(), "0x000000000000000F");
        ASSERT_STREQ(vec[2].getAddressAsShortHexString().c_str(), "0xF");

        ASSERT_STREQ(vec[3].getAddressAsDecimalString().c_str(), "4294967294");
        ASSERT_STREQ(vec[3].getAddressAsFullHexString().c_str(), "0x00000000FFFFFFFE");
        ASSERT_STREQ(vec[3].getAddressAsShortHexString().c_str(), "0xFFFFFFFE");

        ASSERT_STREQ(vec[4].getAddressAsDecimalString().c_str(), "4294967296");
        ASSERT_STREQ(vec[4].getAddressAsFullHexString().c_str(), "0x0000000100000000");
        ASSERT_STREQ(vec[4].getAddressAsShortHexString().c_str(), "0x100000000");

        ASSERT_STREQ(vec[5].getAddressAsDecimalString().c_str(), "18446744073709541615");
        ASSERT_STREQ(vec[5].getAddressAsFullHexString().c_str(), "0xFFFFFFFFFFFFD8EF");
        ASSERT_STREQ(vec[5].getAddressAsShortHexString().c_str(), "0xFFFFFFFFFFFFD8EF");

        ASSERT_STREQ(vec[6].getAddressAsDecimalString().c_str(), "18446744073709551615");
        ASSERT_STREQ(vec[6].getAddressAsFullHexString().c_str(), "0xFFFFFFFFFFFFFFFF");
        ASSERT_STREQ(vec[6].getAddressAsShortHexString().c_str(), "0xFFFFFFFFFFFFFFFF");
    }
}

