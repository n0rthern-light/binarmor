#include <gtest/gtest.h>
#include <core/file/fstream/fstreamFileReader.hpp>
#include <core/file/Binary.hpp>
#include <shared/value/AddressType.hpp>
#include <core/file/format/pe/PeFormat.hpp>

auto fileReader = new CfstreamFileReader();
auto x86exe = new CPeFormat(new CBinary(fileReader->read("./binaries/windows/x86.exe")));
auto x86dll = new CPeFormat(new CBinary(fileReader->read("./binaries/windows/x86.dll")));
auto x86_64exe = new CPeFormat(new CBinary(fileReader->read("./binaries/windows/x86_64.exe")));
auto x86_64dll = new CPeFormat(new CBinary(fileReader->read("./binaries/windows/x86_64.dll")));

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
	ASSERT_EQ(x86exe->getAddressType(), AddressType::BIT_32);
	ASSERT_EQ(x86dll->getAddressType(), AddressType::BIT_32);
	ASSERT_EQ(x86_64exe->getAddressType(), AddressType::BIT_64);
	ASSERT_EQ(x86_64dll->getAddressType(), AddressType::BIT_64);
}

TEST(PeFormatTest, CanResolveEntryPoint)
{
	ASSERT_EQ(x86exe->getEntryPoint().getAddress(), 0x13F0);
	ASSERT_EQ(x86dll->getEntryPoint().getAddress(), 0x13A0);
	ASSERT_EQ(x86_64exe->getEntryPoint().getAddress(), 0x13F0);
	ASSERT_EQ(x86_64dll->getEntryPoint().getAddress(), 0x1330);
}

