#include <gtest/gtest.h>
#include "../../BinaryMother.hpp"
#include "shared/value/Unsigned.hpp"
#include <vector>
#include <stdio.h>

auto x86exe_Sections = BinaryMother::x86exe()->peSections();
auto x86dll_Sections = BinaryMother::x86dll()->peSections();
auto x86_64exe_Sections = BinaryMother::x86_64exe()->peSections();
auto x86_64dll_Sections = BinaryMother::x86_64dll()->peSections();

TEST(PeSectionTest, EqOperandTest)
{
    auto one = CPeSection(".text", 0, CUnsigned(0x600), 0x7800, CUnsigned(0x1000), 0x7634, CUnsigned(0), 0, 0, 0x60000060);
    auto two = CPeSection(".text", 0, CUnsigned(0x600), 0x7800, CUnsigned(0x1000), 0x7634, CUnsigned(0), 0, 0, 0x60000060);
    auto three = CPeSection(".text", 0, CUnsigned(0x600), 0x7800, CUnsigned(0x1000), 0x7634, CUnsigned(0), 0, 0, 0x60000061);
    auto four = CPeSection(".tex", 0, CUnsigned(0x600), 0x7800, CUnsigned(0x1000), 0x7634, CUnsigned(0), 0, 0, 0x60000060);
    auto five = CPeSection(".text", 0, CUnsigned(0x6001), 0x7800, CUnsigned(0x1000), 0x7634, CUnsigned(0), 0, 0, 0x60000060);

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
        CPeSection(".text", 376, CUnsigned(0x600), 0x7800, CUnsigned(0x1000), 0x7634, CUnsigned(0), 0, 0, 0x60000060),
        CPeSection(".data", 416, CUnsigned(0x7E00), 0x200, CUnsigned(0x9000), 0x4C, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".rdata", 456, CUnsigned(0x8000), 0xA00, CUnsigned(0xA000), 0x958, CUnsigned(0), 0, 0, 0x40000040),
        CPeSection(".bss", 496, CUnsigned(0), 0, CUnsigned(0xB000), 0xA54, CUnsigned(0), 0, 0, 0xC0000080),
        CPeSection(".idata", 536, CUnsigned(0x8A00), 0x600, CUnsigned(0xC000), 0x57C, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".CRT", 576, CUnsigned(0x9000), 0x200, CUnsigned(0xD000), 0x30, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".tls", 616, CUnsigned(0x9200), 0x200, CUnsigned(0xE000), 0x8, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".reloc", 656, CUnsigned(0x9400), 0x400, CUnsigned(0xF000), 0x3F8, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/4", 696, CUnsigned(0x9800), 0x600, CUnsigned(0x10000), 0x468, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/19", 736, CUnsigned(0x9E00), 0x12400, CUnsigned(0x11000), 0x123FA, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/31", 776, CUnsigned(0x1C200), 0x3600, CUnsigned(0x24000), 0x344C, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/45", 816, CUnsigned(0x1F800), 0x7600, CUnsigned(0x28000), 0x7560, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/57", 856, CUnsigned(0x26E00), 0x1400, CUnsigned(0x30000), 0x13D8, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/70", 896, CUnsigned(0x28200), 0x600, CUnsigned(0x32000), 0x40D, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/81", 936, CUnsigned(0x28800), 0x3200, CUnsigned(0x33000), 0x300F, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/97", 976, CUnsigned(0x2BA00), 0x7400, CUnsigned(0x37000), 0x7308, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/113", 1016, CUnsigned(0x32E00), 0x600, CUnsigned(0x3F000), 0x5AE, CUnsigned(0), 0, 0, 0x42000040)
    };

    ASSERT_EQ(tested.size(), expected.size());

    for(size_t i = 0; i < expected.size(); i++)
    {
        auto binarySection = *tested[i];
        auto expectedSection = expected[i];

        printf("[%d] Testing section: %s\n", (int)i, expectedSection.name().c_str());

        ASSERT_EQ(binarySection.name(), expectedSection.name());
        ASSERT_EQ(binarySection.headerOffset(), expectedSection.headerOffset());
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
        CPeSection(".text", 376, CUnsigned(0x600), 0x7600, CUnsigned(0x1000), 0x7464, CUnsigned(0), 0, 0, 0x60000060),
        CPeSection(".data", 416, CUnsigned(0x7C00), 0x200, CUnsigned(0x9000), 0x50, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".rdata", 456, CUnsigned(0x7E00), 0x800, CUnsigned(0xA000), 0x7AC, CUnsigned(0), 0, 0, 0x40000040),
        CPeSection(".bss", 496, CUnsigned(0), 0, CUnsigned(0xB000), 0xA30, CUnsigned(0), 0, 0, 0xC0000080),
        CPeSection(".edata", 536, CUnsigned(0x8600), 0x200, CUnsigned(0xC000), 0x47, CUnsigned(0), 0, 0, 0x40000040),
        CPeSection(".idata", 576, CUnsigned(0x8800), 0x600, CUnsigned(0xD000), 0x454, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".CRT", 616, CUnsigned(0x8E00), 0x200, CUnsigned(0xE000), 0x2C, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".tls", 656, CUnsigned(0x9000), 0x200, CUnsigned(0xF000), 0x8, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".reloc", 696, CUnsigned(0x9200), 0x400, CUnsigned(0x10000), 0x39C, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/4", 736, CUnsigned(0x9600), 0x400, CUnsigned(0x11000), 0x3B0, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/19", 776, CUnsigned(0x9A00), 0x10400, CUnsigned(0x12000), 0x102F7, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/31", 816, CUnsigned(0x19E00), 0x3000, CUnsigned(0x23000), 0x2FDE, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/45", 856, CUnsigned(0x1CE00), 0x7400, CUnsigned(0x26000), 0x729B, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/57", 896, CUnsigned(0x24200), 0x1400, CUnsigned(0x2E000), 0x13D0, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/70", 936, CUnsigned(0x25600), 0x400, CUnsigned(0x30000), 0x23F, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/81", 976, CUnsigned(0x25A00), 0x2A00, CUnsigned(0x31000), 0x2887, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/97", 1016, CUnsigned(0x28400), 0x7400, CUnsigned(0x34000), 0x7318, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/113", 1056, CUnsigned(0x2F800), 0x600, CUnsigned(0x3C000), 0x585, CUnsigned(0), 0, 0, 0x42000040)
    };

    ASSERT_EQ(tested.size(), expected.size());

    for(size_t i = 0; i < expected.size(); i++)
    {
        auto binarySection = *tested[i];
        auto expectedSection = expected[i];

        printf("[%d] Testing section: %s\n", (int)i, expectedSection.name().c_str());

        ASSERT_EQ(binarySection.name(), expectedSection.name());
        ASSERT_EQ(binarySection.headerOffset(), expectedSection.headerOffset());
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
        CPeSection(".text", 392, CUnsigned(0x600), 0x7200, CUnsigned(0x1000), 0x71E8, CUnsigned(0), 0, 0, 0x60000060),
        CPeSection(".data", 432, CUnsigned(0x7800), 0x200, CUnsigned(0x9000), 0xC0, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".rdata", 472, CUnsigned(0x7A00), 0xE00, CUnsigned(0xA000), 0xDA0, CUnsigned(0), 0, 0, 0x40000040),
        CPeSection(".pdata", 512, CUnsigned(0x8800), 0x600, CUnsigned(0xB000), 0x468, CUnsigned(0), 0, 0, 0x40000040),
        CPeSection(".xdata", 552, CUnsigned(0x8E00), 0x600, CUnsigned(0xC000), 0x42C, CUnsigned(0), 0, 0, 0x40000040),
        CPeSection(".bss", 592, CUnsigned(0), 0, CUnsigned(0xD000), 0xB80, CUnsigned(0), 0, 0, 0xC0000080),
        CPeSection(".idata", 632, CUnsigned(0x9400), 0x800, CUnsigned(0xE000), 0x6D0, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".CRT", 672, CUnsigned(0x9C00), 0x200, CUnsigned(0xF000), 0x60, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".tls", 712, CUnsigned(0x9E00), 0x200, CUnsigned(0x10000), 0x10, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".reloc", 752, CUnsigned(0xA000), 0x200, CUnsigned(0x11000), 0x84, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/4", 792, CUnsigned(0xA200), 0x800, CUnsigned(0x12000), 0x670, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/19", 832, CUnsigned(0xAA00), 0x13200, CUnsigned(0x13000), 0x131A7, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/31", 872, CUnsigned(0x1DC00), 0x3400, CUnsigned(0x27000), 0x3309, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/45", 912, CUnsigned(0x21000), 0x7400, CUnsigned(0x2B000), 0x7348, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/57", 952, CUnsigned(0x28400), 0x1800, CUnsigned(0x33000), 0x16E0, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/70", 992, CUnsigned(0x29C00), 0x600, CUnsigned(0x35000), 0x438, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/81", 1032, CUnsigned(0x2A200), 0x3200, CUnsigned(0x36000), 0x302B, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/97", 1072, CUnsigned(0x2D400), 0x8000, CUnsigned(0x3A000), 0x7F69, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/113", 1112, CUnsigned(0x35400), 0x600, CUnsigned(0x42000), 0x5AF, CUnsigned(0), 0, 0, 0x42000040)
    };

    ASSERT_EQ(tested.size(), expected.size());

    for(size_t i = 0; i < expected.size(); i++)
    {
        auto binarySection = *tested[i];
        auto expectedSection = expected[i];

        printf("[%d] Testing section: %s\n", (int)i, expectedSection.name().c_str());

        ASSERT_EQ(binarySection.name(), expectedSection.name());
        ASSERT_EQ(binarySection.headerOffset(), expectedSection.headerOffset());
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
        CPeSection(".text", 392, CUnsigned(0x600), 0x7000, CUnsigned(0x1000), 0x6EE8, CUnsigned(0), 0, 0, 0x60000060),
        CPeSection(".data", 432, CUnsigned(0x7600), 0x200, CUnsigned(0x8000), 0xB0, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".rdata", 472, CUnsigned(0x7800), 0xC00, CUnsigned(0x9000), 0xA30, CUnsigned(0), 0, 0, 0x40000040),
        CPeSection(".pdata", 512, CUnsigned(0x8400), 0x600, CUnsigned(0xA000), 0x420, CUnsigned(0), 0, 0, 0x40000040),
        CPeSection(".xdata", 552, CUnsigned(0x8A00), 0x400, CUnsigned(0xB000), 0x3D8, CUnsigned(0), 0, 0, 0x40000040),
        CPeSection(".bss", 592, CUnsigned(0), 0, CUnsigned(0xC000), 0xB10, CUnsigned(0), 0, 0, 0xC0000080),
        CPeSection(".edata", 632, CUnsigned(0x8E00), 0x200, CUnsigned(0xD000), 0x4A, CUnsigned(0), 0, 0, 0x40000040),
        CPeSection(".idata", 672, CUnsigned(0x9000), 0x600, CUnsigned(0xE000), 0x52C, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".CRT", 712, CUnsigned(0x9600), 0x200, CUnsigned(0xF000), 0x58, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".tls", 752, CUnsigned(0x9800), 0x200, CUnsigned(0x10000), 0x10, CUnsigned(0), 0, 0, 0xC0000040),
        CPeSection(".reloc", 792, CUnsigned(0x9A00), 0x200, CUnsigned(0x11000), 0x64, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/4", 832, CUnsigned(0x9C00), 0x600, CUnsigned(0x12000), 0x510, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/19", 872, CUnsigned(0xA200), 0x10C00, CUnsigned(0x13000), 0x10A76, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/31", 912, CUnsigned(0x1AE00), 0x2E00, CUnsigned(0x24000), 0x2CF2, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/45", 952, CUnsigned(0x1DC00), 0x7000, CUnsigned(0x27000), 0x6F6D, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/57", 992, CUnsigned(0x24C00), 0x1600, CUnsigned(0x2E000), 0x15D8, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/70", 1032, CUnsigned(0x26200), 0x400, CUnsigned(0x30000), 0x26A, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/81", 1072, CUnsigned(0x26600), 0x2800, CUnsigned(0x31000), 0x26A3, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/97", 1112, CUnsigned(0x28E00), 0x8000, CUnsigned(0x34000), 0x7EED, CUnsigned(0), 0, 0, 0x42000040),
        CPeSection("/113", 1152, CUnsigned(0x30E00), 0x600, CUnsigned(0x3C000), 0x5B0, CUnsigned(0), 0, 0, 0x42000040)
    };

    ASSERT_EQ(tested.size(), expected.size());

    for(size_t i = 0; i < expected.size(); i++)
    {
        auto binarySection = *tested[i];
        auto expectedSection = expected[i];

        printf("[%d] Testing section: %s\n", (int)i, expectedSection.name().c_str());

        ASSERT_EQ(binarySection.name(), expectedSection.name());
        ASSERT_EQ(binarySection.headerOffset(), expectedSection.headerOffset());
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

