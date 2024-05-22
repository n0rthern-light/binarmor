#include <gtest/gtest.h>
#include "../../BinaryMother.hpp"
#include <shared/value/AddressType.hpp>

auto x86exe = BinaryMother::x86exe();
auto x86dll = BinaryMother::x86dll();
auto x86_64exe = BinaryMother::x86_64exe();
auto x86_64dll = BinaryMother::x86_64dll();

TEST(PeFormatTest, CanRecognizeArchitecture)
{
	ASSERT_EQ(x86exe->getArchitecture(), Architecture::X86);
	ASSERT_EQ(x86dll->getArchitecture(), Architecture::X86);
	ASSERT_EQ(x86_64exe->getArchitecture(), Architecture::X86_64);
	ASSERT_EQ(x86_64dll->getArchitecture(), Architecture::X86_64);
}

TEST(PeFormatTest, CanRecognizeType)
{
	ASSERT_EQ(x86exe->getType(), Type::Executable);
	ASSERT_EQ(x86dll->getType(), Type::Dynamic_Library);
	ASSERT_EQ(x86_64exe->getType(), Type::Executable);
	ASSERT_EQ(x86_64dll->getType(), Type::Dynamic_Library);
}

TEST(PeFormatTest, CanRecognizeEndianness)
{
	ASSERT_EQ(x86exe->getEndianness(), Endianness::LITTLE);
	ASSERT_EQ(x86dll->getEndianness(), Endianness::LITTLE);
	ASSERT_EQ(x86_64exe->getEndianness(), Endianness::LITTLE);
	ASSERT_EQ(x86_64dll->getEndianness(), Endianness::LITTLE);
}

TEST(PeFormatTest, CanRecognizeAddressType)
{
	ASSERT_EQ(x86exe->getAddressType(), AddressType::_32_BIT);
	ASSERT_EQ(x86dll->getAddressType(), AddressType::_32_BIT);
	ASSERT_EQ(x86_64exe->getAddressType(), AddressType::_64_BIT);
	ASSERT_EQ(x86_64dll->getAddressType(), AddressType::_64_BIT);
}

TEST(PeFormatTest, CanResolveEntryPoint)
{
	ASSERT_EQ(x86exe->getEntryPoint().getAddress(), 0x13F0);
	ASSERT_EQ(x86dll->getEntryPoint().getAddress(), 0x13A0);
	ASSERT_EQ(x86_64exe->getEntryPoint().getAddress(), 0x13F0);
	ASSERT_EQ(x86_64dll->getEntryPoint().getAddress(), 0x1330);
}

