#include <gtest/gtest.h>
#include "shared/value/Unsigned.hpp"
#include "shared/types/defines.hpp"
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

    {
        SCOPED_TRACE("Testing reading as little endian");

        ASSERT_EQ(vec[0].asLittleEndianBytes(1), (byte_vec { 0x00 }));
        ASSERT_EQ(vec[0].asLittleEndianBytes(2), (byte_vec { 0x00, 0x00 }));
        ASSERT_EQ(vec[0].asLittleEndianBytes(3), (byte_vec { 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[0].asLittleEndianBytes(4), (byte_vec { 0x00, 0x00, 0x00, 0x00 }));

        ASSERT_EQ(vec[1].asLittleEndianBytes(1), (byte_vec { 0x0A }));
        ASSERT_EQ(vec[1].asLittleEndianBytes(2), (byte_vec { 0x0A, 0x00, }));
        ASSERT_EQ(vec[1].asLittleEndianBytes(3), (byte_vec { 0x0A, 0x00, 0x00 }));
        ASSERT_EQ(vec[1].asLittleEndianBytes(4), (byte_vec { 0x0A, 0x00, 0x00, 0x00 }));

        ASSERT_EQ(vec[2].asLittleEndianBytes(1), (byte_vec { 0x0F }));
        ASSERT_EQ(vec[2].asLittleEndianBytes(2), (byte_vec { 0x0F, 0x00, }));
        ASSERT_EQ(vec[2].asLittleEndianBytes(3), (byte_vec { 0x0F, 0x00, 0x00 }));
        ASSERT_EQ(vec[2].asLittleEndianBytes(4), (byte_vec { 0x0F, 0x00, 0x00, 0x00 }));

        ASSERT_EQ(vec[3].asLittleEndianBytes(1), (byte_vec { 0xFE }));
        ASSERT_EQ(vec[3].asLittleEndianBytes(2), (byte_vec { 0xFE, 0xFF, }));
        ASSERT_EQ(vec[3].asLittleEndianBytes(3), (byte_vec { 0xFE, 0xFF, 0xFF }));
        ASSERT_EQ(vec[3].asLittleEndianBytes(4), (byte_vec { 0xFE, 0xFF, 0xFF, 0xFF }));

        ASSERT_EQ(vec[4].asLittleEndianBytes(1), (byte_vec { 0xFF }));
        ASSERT_EQ(vec[4].asLittleEndianBytes(2), (byte_vec { 0xFF, 0xFF, }));
        ASSERT_EQ(vec[4].asLittleEndianBytes(3), (byte_vec { 0xFF, 0xFF, 0xFF }));
        ASSERT_EQ(vec[4].asLittleEndianBytes(4), (byte_vec { 0xFF, 0xFF, 0xFF, 0xFF }));
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

    {
        SCOPED_TRACE("Testing reading as little endian");

        ASSERT_EQ(vec[0].asLittleEndianBytes(1), (byte_vec { 0x00 }));
        ASSERT_EQ(vec[0].asLittleEndianBytes(2), (byte_vec { 0x00, 0x00 }));
        ASSERT_EQ(vec[0].asLittleEndianBytes(3), (byte_vec { 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[0].asLittleEndianBytes(4), (byte_vec { 0x00, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[0].asLittleEndianBytes(5), (byte_vec { 0x00, 0x00, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[0].asLittleEndianBytes(6), (byte_vec { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[0].asLittleEndianBytes(7), (byte_vec { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[0].asLittleEndianBytes(8), (byte_vec { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }));

        ASSERT_EQ(vec[1].asLittleEndianBytes(1), (byte_vec { 0x0A }));
        ASSERT_EQ(vec[1].asLittleEndianBytes(2), (byte_vec { 0x0A, 0x00, }));
        ASSERT_EQ(vec[1].asLittleEndianBytes(3), (byte_vec { 0x0A, 0x00, 0x00 }));
        ASSERT_EQ(vec[1].asLittleEndianBytes(4), (byte_vec { 0x0A, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[1].asLittleEndianBytes(5), (byte_vec { 0x0A, 0x00, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[1].asLittleEndianBytes(6), (byte_vec { 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[1].asLittleEndianBytes(7), (byte_vec { 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[1].asLittleEndianBytes(8), (byte_vec { 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }));

        ASSERT_EQ(vec[2].asLittleEndianBytes(1), (byte_vec { 0x0F }));
        ASSERT_EQ(vec[2].asLittleEndianBytes(2), (byte_vec { 0x0F, 0x00, }));
        ASSERT_EQ(vec[2].asLittleEndianBytes(3), (byte_vec { 0x0F, 0x00, 0x00 }));
        ASSERT_EQ(vec[2].asLittleEndianBytes(4), (byte_vec { 0x0F, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[2].asLittleEndianBytes(5), (byte_vec { 0x0F, 0x00, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[2].asLittleEndianBytes(6), (byte_vec { 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[2].asLittleEndianBytes(7), (byte_vec { 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[2].asLittleEndianBytes(8), (byte_vec { 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }));

        ASSERT_EQ(vec[3].asLittleEndianBytes(1), (byte_vec { 0xFE }));
        ASSERT_EQ(vec[3].asLittleEndianBytes(2), (byte_vec { 0xFE, 0xFF, }));
        ASSERT_EQ(vec[3].asLittleEndianBytes(3), (byte_vec { 0xFE, 0xFF, 0xFF }));
        ASSERT_EQ(vec[3].asLittleEndianBytes(4), (byte_vec { 0xFE, 0xFF, 0xFF, 0xFF }));
        ASSERT_EQ(vec[3].asLittleEndianBytes(5), (byte_vec { 0xFE, 0xFF, 0xFF, 0xFF, 0x00 }));
        ASSERT_EQ(vec[3].asLittleEndianBytes(6), (byte_vec { 0xFE, 0xFF, 0xFF, 0xFF, 0x00, 0x00 }));
        ASSERT_EQ(vec[3].asLittleEndianBytes(7), (byte_vec { 0xFE, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[3].asLittleEndianBytes(8), (byte_vec { 0xFE, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00 }));

        ASSERT_EQ(vec[4].asLittleEndianBytes(1), (byte_vec { 0x00 }));
        ASSERT_EQ(vec[4].asLittleEndianBytes(2), (byte_vec { 0x00, 0x00, }));
        ASSERT_EQ(vec[4].asLittleEndianBytes(3), (byte_vec { 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[4].asLittleEndianBytes(4), (byte_vec { 0x00, 0x00, 0x00, 0x00 }));
        ASSERT_EQ(vec[4].asLittleEndianBytes(5), (byte_vec { 0x00, 0x00, 0x00, 0x00, 0x01 }));
        ASSERT_EQ(vec[4].asLittleEndianBytes(6), (byte_vec { 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 }));
        ASSERT_EQ(vec[4].asLittleEndianBytes(7), (byte_vec { 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 }));
        ASSERT_EQ(vec[4].asLittleEndianBytes(8), (byte_vec { 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 }));

        ASSERT_EQ(vec[5].asLittleEndianBytes(1), (byte_vec { 0xEF }));
        ASSERT_EQ(vec[5].asLittleEndianBytes(2), (byte_vec { 0xEF, 0xD8, }));
        ASSERT_EQ(vec[5].asLittleEndianBytes(3), (byte_vec { 0xEF, 0xD8, 0xFF }));
        ASSERT_EQ(vec[5].asLittleEndianBytes(4), (byte_vec { 0xEF, 0xD8, 0xFF, 0xFF }));
        ASSERT_EQ(vec[5].asLittleEndianBytes(5), (byte_vec { 0xEF, 0xD8, 0xFF, 0xFF, 0xFF }));
        ASSERT_EQ(vec[5].asLittleEndianBytes(6), (byte_vec { 0xEF, 0xD8, 0xFF, 0xFF, 0xFF, 0xFF }));
        ASSERT_EQ(vec[5].asLittleEndianBytes(7), (byte_vec { 0xEF, 0xD8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }));
        ASSERT_EQ(vec[5].asLittleEndianBytes(8), (byte_vec { 0xEF, 0xD8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }));

        ASSERT_EQ(vec[6].asLittleEndianBytes(1), (byte_vec { 0xFF }));
        ASSERT_EQ(vec[6].asLittleEndianBytes(2), (byte_vec { 0xFF, 0xFF, }));
        ASSERT_EQ(vec[6].asLittleEndianBytes(3), (byte_vec { 0xFF, 0xFF, 0xFF }));
        ASSERT_EQ(vec[6].asLittleEndianBytes(4), (byte_vec { 0xFF, 0xFF, 0xFF, 0xFF }));
        ASSERT_EQ(vec[6].asLittleEndianBytes(5), (byte_vec { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }));
        ASSERT_EQ(vec[6].asLittleEndianBytes(6), (byte_vec { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }));
        ASSERT_EQ(vec[6].asLittleEndianBytes(7), (byte_vec { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }));
        ASSERT_EQ(vec[6].asLittleEndianBytes(8), (byte_vec { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }));
    }
}

