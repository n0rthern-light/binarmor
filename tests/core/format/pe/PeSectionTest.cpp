#include <gtest/gtest.h>
#include "../../BinaryMother.hpp"
#include "shared/value/AddressValue.hpp"
#include <vector>
#include <stdio.h>

auto x86exe_Sections = BinaryMother::x86exe()->sections();
auto x86dll_Sections = BinaryMother::x86dll()->sections();
auto x86_64exe_Sections = BinaryMother::x86_64exe()->sections();
auto x86_64dll_Sections = BinaryMother::x86_64dll()->sections();

TEST(PeSectionTest, EqOperandTest)
{
	auto one = CPeSection(".text", CAddressValue(0x600), 0x7800, CAddressValue(0x1000), 0x7634, CAddressValue(0), 0, 0, 0x60000060);
	auto two = CPeSection(".text", CAddressValue(0x600), 0x7800, CAddressValue(0x1000), 0x7634, CAddressValue(0), 0, 0, 0x60000060);
	auto three = CPeSection(".text", CAddressValue(0x600), 0x7800, CAddressValue(0x1000), 0x7634, CAddressValue(0), 0, 0, 0x60000061);
	auto four = CPeSection(".tex", CAddressValue(0x600), 0x7800, CAddressValue(0x1000), 0x7634, CAddressValue(0), 0, 0, 0x60000060);
	auto five = CPeSection(".text", CAddressValue(0x6001), 0x7800, CAddressValue(0x1000), 0x7634, CAddressValue(0), 0, 0, 0x60000060);

	ASSERT_TRUE(one == two);

	ASSERT_FALSE(one == three);
	ASSERT_FALSE(two == three);

	ASSERT_FALSE(one == four);
	ASSERT_FALSE(two == four);

	ASSERT_FALSE(one == five);
	ASSERT_FALSE(two == five);
}

TEST(PeSectionTest, X86ExeSectionsAreCorrect)
{
	auto tested = x86exe_Sections;

	auto expected = std::vector<CPeSection> {
		CPeSection(".text", CAddressValue(0x600), 0x7800, CAddressValue(0x1000), 0x7634, CAddressValue(0), 0, 0, 0x60000060),
		CPeSection(".data", CAddressValue(0x7E00), 0x200, CAddressValue(0x9000), 0x4C, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".rdata", CAddressValue(0x8000), 0xA00, CAddressValue(0xA000), 0x958, CAddressValue(0), 0, 0, 0x40000040),
		CPeSection(".bss", CAddressValue(0), 0, CAddressValue(0xB000), 0xA54, CAddressValue(0), 0, 0, 0xC0000080),
		CPeSection(".idata", CAddressValue(0x8A00), 0x600, CAddressValue(0xC000), 0x57C, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".CRT", CAddressValue(0x9000), 0x200, CAddressValue(0xD000), 0x30, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".tls", CAddressValue(0x9200), 0x200, CAddressValue(0xE000), 0x8, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".reloc", CAddressValue(0x9400), 0x400, CAddressValue(0xF000), 0x3F8, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/4", CAddressValue(0x9800), 0x600, CAddressValue(0x10000), 0x468, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/19", CAddressValue(0x9E00), 0x12400, CAddressValue(0x11000), 0x123FA, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/31", CAddressValue(0x1C200), 0x3600, CAddressValue(0x24000), 0x344C, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/45", CAddressValue(0x1F800), 0x7600, CAddressValue(0x28000), 0x7560, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/57", CAddressValue(0x26E00), 0x1400, CAddressValue(0x30000), 0x13D8, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/70", CAddressValue(0x28200), 0x600, CAddressValue(0x32000), 0x40D, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/81", CAddressValue(0x28800), 0x3200, CAddressValue(0x33000), 0x300F, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/97", CAddressValue(0x2BA00), 0x7400, CAddressValue(0x37000), 0x7308, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/113", CAddressValue(0x32E00), 0x600, CAddressValue(0x3F000), 0x5AE, CAddressValue(0), 0, 0, 0x42000040)
	};

	ASSERT_EQ(tested.size(), expected.size());

	for(size_t i = 0; i < expected.size(); i++)
	{
		auto binarySection = *tested[i];
		auto expectedSection = expected[i];

		printf("[%d] Testing section: %s\n", (int)i, expectedSection.name().c_str());

		ASSERT_EQ(binarySection.name(), expectedSection.name());
		ASSERT_EQ(binarySection.rawAddress(), expectedSection.rawAddress());
		ASSERT_EQ(binarySection.rawSize(), expectedSection.rawSize());
		ASSERT_EQ(binarySection.virtualAddress(), expectedSection.virtualAddress());
		ASSERT_EQ(binarySection.virtualSize(), expectedSection.virtualSize());
		ASSERT_EQ(binarySection.pointerToRelocations(), expectedSection.pointerToRelocations());
		ASSERT_EQ(binarySection.numberOfLinenumbers(), expectedSection.numberOfLinenumbers());
		ASSERT_EQ(binarySection.numberOfRelocations(), expectedSection.numberOfRelocations());
		ASSERT_EQ(binarySection.characteristics(), expectedSection.characteristics());
	}
}

TEST(PeSectionTest, X86DllSectionsAreCorrect)
{
	auto tested = x86dll_Sections;

	auto expected = std::vector<CPeSection> {
		CPeSection(".text", CAddressValue(0x600), 0x7600, CAddressValue(0x1000), 0x7464, CAddressValue(0), 0, 0, 0x60000060),
		CPeSection(".data", CAddressValue(0x7C00), 0x200, CAddressValue(0x9000), 0x50, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".rdata", CAddressValue(0x7E00), 0x800, CAddressValue(0xA000), 0x7AC, CAddressValue(0), 0, 0, 0x40000040),
		CPeSection(".bss", CAddressValue(0), 0, CAddressValue(0xB000), 0xA30, CAddressValue(0), 0, 0, 0xC0000080),
		CPeSection(".edata", CAddressValue(0x8600), 0x200, CAddressValue(0xC000), 0x47, CAddressValue(0), 0, 0, 0x40000040),
		CPeSection(".idata", CAddressValue(0x8800), 0x600, CAddressValue(0xD000), 0x454, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".CRT", CAddressValue(0x8E00), 0x200, CAddressValue(0xE000), 0x2C, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".tls", CAddressValue(0x9000), 0x200, CAddressValue(0xF000), 0x8, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".reloc", CAddressValue(0x9200), 0x400, CAddressValue(0x10000), 0x39C, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/4", CAddressValue(0x9600), 0x400, CAddressValue(0x11000), 0x3B0, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/19", CAddressValue(0x9A00), 0x10400, CAddressValue(0x12000), 0x102F7, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/31", CAddressValue(0x19E00), 0x3000, CAddressValue(0x23000), 0x2FDE, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/45", CAddressValue(0x1CE00), 0x7400, CAddressValue(0x26000), 0x729B, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/57", CAddressValue(0x24200), 0x1400, CAddressValue(0x2E000), 0x13D0, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/70", CAddressValue(0x25600), 0x400, CAddressValue(0x30000), 0x23F, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/81", CAddressValue(0x25A00), 0x2A00, CAddressValue(0x31000), 0x2887, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/97", CAddressValue(0x28400), 0x7400, CAddressValue(0x34000), 0x7318, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/113", CAddressValue(0x2F800), 0x600, CAddressValue(0x3C000), 0x585, CAddressValue(0), 0, 0, 0x42000040)
	};

	ASSERT_EQ(tested.size(), expected.size());

	for(size_t i = 0; i < expected.size(); i++)
	{
		auto binarySection = *tested[i];
		auto expectedSection = expected[i];

		printf("[%d] Testing section: %s\n", (int)i, expectedSection.name().c_str());

		ASSERT_EQ(binarySection.name(), expectedSection.name());
		ASSERT_EQ(binarySection.rawAddress(), expectedSection.rawAddress());
		ASSERT_EQ(binarySection.rawSize(), expectedSection.rawSize());
		ASSERT_EQ(binarySection.virtualAddress(), expectedSection.virtualAddress());
		ASSERT_EQ(binarySection.virtualSize(), expectedSection.virtualSize());
		ASSERT_EQ(binarySection.pointerToRelocations(), expectedSection.pointerToRelocations());
		ASSERT_EQ(binarySection.numberOfLinenumbers(), expectedSection.numberOfLinenumbers());
		ASSERT_EQ(binarySection.numberOfRelocations(), expectedSection.numberOfRelocations());
		ASSERT_EQ(binarySection.characteristics(), expectedSection.characteristics());
	}
}

TEST(PeSectionTest, X86_64ExeSectionsAreCorrect)
{
	auto tested = x86_64exe_Sections;

	auto expected = std::vector<CPeSection> {
		CPeSection(".text", CAddressValue(0x600), 0x7200, CAddressValue(0x1000), 0x71E8, CAddressValue(0), 0, 0, 0x60000060),
		CPeSection(".data", CAddressValue(0x7800), 0x200, CAddressValue(0x9000), 0xC0, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".rdata", CAddressValue(0x7A00), 0xE00, CAddressValue(0xA000), 0xDA0, CAddressValue(0), 0, 0, 0x40000040),
		CPeSection(".pdata", CAddressValue(0x8800), 0x600, CAddressValue(0xB000), 0x468, CAddressValue(0), 0, 0, 0x40000040),
		CPeSection(".xdata", CAddressValue(0x8E00), 0x600, CAddressValue(0xC000), 0x42C, CAddressValue(0), 0, 0, 0x40000040),
		CPeSection(".bss", CAddressValue(0), 0, CAddressValue(0xD000), 0xB80, CAddressValue(0), 0, 0, 0xC0000080),
		CPeSection(".idata", CAddressValue(0x9400), 0x800, CAddressValue(0xE000), 0x6D0, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".CRT", CAddressValue(0x9C00), 0x200, CAddressValue(0xF000), 0x60, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".tls", CAddressValue(0x9E00), 0x200, CAddressValue(0x10000), 0x10, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".reloc", CAddressValue(0xA000), 0x200, CAddressValue(0x11000), 0x84, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/4", CAddressValue(0xA200), 0x800, CAddressValue(0x12000), 0x670, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/19", CAddressValue(0xAA00), 0x13200, CAddressValue(0x13000), 0x131A7, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/31", CAddressValue(0x1DC00), 0x3400, CAddressValue(0x27000), 0x3309, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/45", CAddressValue(0x21000), 0x7400, CAddressValue(0x2B000), 0x7348, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/57", CAddressValue(0x28400), 0x1800, CAddressValue(0x33000), 0x16E0, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/70", CAddressValue(0x29C00), 0x600, CAddressValue(0x35000), 0x438, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/81", CAddressValue(0x2A200), 0x3200, CAddressValue(0x36000), 0x302B, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/97", CAddressValue(0x2D400), 0x8000, CAddressValue(0x3A000), 0x7F69, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/113", CAddressValue(0x35400), 0x600, CAddressValue(0x42000), 0x5AF, CAddressValue(0), 0, 0, 0x42000040)
	};

	ASSERT_EQ(tested.size(), expected.size());

	for(size_t i = 0; i < expected.size(); i++)
	{
		auto binarySection = *tested[i];
		auto expectedSection = expected[i];

		printf("[%d] Testing section: %s\n", (int)i, expectedSection.name().c_str());

		ASSERT_EQ(binarySection.name(), expectedSection.name());
		ASSERT_EQ(binarySection.rawAddress(), expectedSection.rawAddress());
		ASSERT_EQ(binarySection.rawSize(), expectedSection.rawSize());
		ASSERT_EQ(binarySection.virtualAddress(), expectedSection.virtualAddress());
		ASSERT_EQ(binarySection.virtualSize(), expectedSection.virtualSize());
		ASSERT_EQ(binarySection.pointerToRelocations(), expectedSection.pointerToRelocations());
		ASSERT_EQ(binarySection.numberOfLinenumbers(), expectedSection.numberOfLinenumbers());
		ASSERT_EQ(binarySection.numberOfRelocations(), expectedSection.numberOfRelocations());
		ASSERT_EQ(binarySection.characteristics(), expectedSection.characteristics());
	}
}

TEST(PeSectionTest, X86_64DllSectionsAreCorrect)
{
	auto tested = x86_64dll_Sections;

	auto expected = std::vector<CPeSection> {
		CPeSection(".text", CAddressValue(0x600), 0x7000, CAddressValue(0x1000), 0x6EE8, CAddressValue(0), 0, 0, 0x60000060),
		CPeSection(".data", CAddressValue(0x7600), 0x200, CAddressValue(0x8000), 0xB0, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".rdata", CAddressValue(0x7800), 0xC00, CAddressValue(0x9000), 0xA30, CAddressValue(0), 0, 0, 0x40000040),
		CPeSection(".pdata", CAddressValue(0x8400), 0x600, CAddressValue(0xA000), 0x420, CAddressValue(0), 0, 0, 0x40000040),
		CPeSection(".xdata", CAddressValue(0x8A00), 0x400, CAddressValue(0xB000), 0x3D8, CAddressValue(0), 0, 0, 0x40000040),
		CPeSection(".bss", CAddressValue(0), 0, CAddressValue(0xC000), 0xB10, CAddressValue(0), 0, 0, 0xC0000080),
		CPeSection(".edata", CAddressValue(0x8E00), 0x200, CAddressValue(0xD000), 0x4A, CAddressValue(0), 0, 0, 0x40000040),
		CPeSection(".idata", CAddressValue(0x9000), 0x600, CAddressValue(0xE000), 0x52C, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".CRT", CAddressValue(0x9600), 0x200, CAddressValue(0xF000), 0x58, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".tls", CAddressValue(0x9800), 0x200, CAddressValue(0x10000), 0x10, CAddressValue(0), 0, 0, 0xC0000040),
		CPeSection(".reloc", CAddressValue(0x9A00), 0x200, CAddressValue(0x11000), 0x64, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/4", CAddressValue(0x9C00), 0x600, CAddressValue(0x12000), 0x510, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/19", CAddressValue(0xA200), 0x10C00, CAddressValue(0x13000), 0x10A76, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/31", CAddressValue(0x1AE00), 0x2E00, CAddressValue(0x24000), 0x2CF2, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/45", CAddressValue(0x1DC00), 0x7000, CAddressValue(0x27000), 0x6F6D, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/57", CAddressValue(0x24C00), 0x1600, CAddressValue(0x2E000), 0x15D8, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/70", CAddressValue(0x26200), 0x400, CAddressValue(0x30000), 0x26A, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/81", CAddressValue(0x26600), 0x2800, CAddressValue(0x31000), 0x26A3, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/97", CAddressValue(0x28E00), 0x8000, CAddressValue(0x34000), 0x7EED, CAddressValue(0), 0, 0, 0x42000040),
		CPeSection("/113", CAddressValue(0x30E00), 0x600, CAddressValue(0x3C000), 0x5B0, CAddressValue(0), 0, 0, 0x42000040)
	};

	ASSERT_EQ(tested.size(), expected.size());

	for(size_t i = 0; i < expected.size(); i++)
	{
		auto binarySection = *tested[i];
		auto expectedSection = expected[i];

		printf("[%d] Testing section: %s\n", (int)i, expectedSection.name().c_str());

		ASSERT_EQ(binarySection.name(), expectedSection.name());
		ASSERT_EQ(binarySection.rawAddress(), expectedSection.rawAddress());
		ASSERT_EQ(binarySection.rawSize(), expectedSection.rawSize());
		ASSERT_EQ(binarySection.virtualAddress(), expectedSection.virtualAddress());
		ASSERT_EQ(binarySection.virtualSize(), expectedSection.virtualSize());
		ASSERT_EQ(binarySection.pointerToRelocations(), expectedSection.pointerToRelocations());
		ASSERT_EQ(binarySection.numberOfLinenumbers(), expectedSection.numberOfLinenumbers());
		ASSERT_EQ(binarySection.numberOfRelocations(), expectedSection.numberOfRelocations());
		ASSERT_EQ(binarySection.characteristics(), expectedSection.characteristics());
	}
}

