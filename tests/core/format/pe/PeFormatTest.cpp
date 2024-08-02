#include <gtest/gtest.h>
#include "../../BinaryMother.hpp"
#include "core/format/pe/defines.hpp"
#include "core/shared/SectionPermissions.hpp"
#include "shared/types/defines.hpp"
#include <shared/value/AddressType.hpp>

auto x86exe = BinaryMother::x86exe();
auto x86dll = BinaryMother::x86dll();
auto x86_64exe = BinaryMother::x86_64exe();
auto x86_64dll = BinaryMother::x86_64dll();

TEST(PeFormatTest, CanRecognizeArchitecture)
{
    ASSERT_EQ(x86exe->architecture(), Architecture::X86);
    ASSERT_EQ(x86dll->architecture(), Architecture::X86);
    ASSERT_EQ(x86_64exe->architecture(), Architecture::X86_64);
    ASSERT_EQ(x86_64dll->architecture(), Architecture::X86_64);
}

TEST(PeFormatTest, CanRecognizeType)
{
    ASSERT_EQ(x86exe->type(), Type::Executable);
    ASSERT_EQ(x86dll->type(), Type::Dynamic_Library);
    ASSERT_EQ(x86_64exe->type(), Type::Executable);
    ASSERT_EQ(x86_64dll->type(), Type::Dynamic_Library);
}

TEST(PeFormatTest, CanRecognizeEndianness)
{
    ASSERT_EQ(x86exe->endianness(), Endianness::LITTLE);
    ASSERT_EQ(x86dll->endianness(), Endianness::LITTLE);
    ASSERT_EQ(x86_64exe->endianness(), Endianness::LITTLE);
    ASSERT_EQ(x86_64dll->endianness(), Endianness::LITTLE);
}

TEST(PeFormatTest, CanRecognizeAddressType)
{
    ASSERT_EQ(x86exe->addressType(), AddressType::_32_BIT);
    ASSERT_EQ(x86dll->addressType(), AddressType::_32_BIT);
    ASSERT_EQ(x86_64exe->addressType(), AddressType::_64_BIT);
    ASSERT_EQ(x86_64dll->addressType(), AddressType::_64_BIT);
}

TEST(PeFormatTest, CanResolveEntryPoint)
{
    ASSERT_EQ(x86exe->entryPoint().get(), 0x13F0);
    ASSERT_EQ(x86dll->entryPoint().get(), 0x13A0);
    ASSERT_EQ(x86_64exe->entryPoint().get(), 0x13F0);
    ASSERT_EQ(x86_64dll->entryPoint().get(), 0x1330);
}

TEST(PeFormatTest, CanAddNewSectionsIn32Bit)
{
    constexpr binary_offset SECTION_SIZE = 0x10001;
    const auto permissions = CSectionPermissions { SectionPermissionType::READ };
    auto modified = x86exe->addPeSection(".test_d", SECTION_SIZE, permissions);
    const auto originalSectionCount = x86exe->sectionCount();

    auto originalSections = x86exe->peSections();
    auto modifiedSections = modified.peSections();
    const auto insertedSection = modifiedSections.back();

    ASSERT_EQ(modifiedSections.size(), originalSections.size() + 1);
    ASSERT_EQ(modified.binary().size(), x86exe->binary().size() + insertedSection->rawSize());

    ASSERT_STREQ(insertedSection->name().c_str(), ".test_d");
    ASSERT_EQ(insertedSection->virtualSize(), SECTION_SIZE);
    ASSERT_GE(insertedSection->rawSize(), SECTION_SIZE);
    ASSERT_EQ(insertedSection->permissions(), permissions);
    ASSERT_EQ(insertedSection->characteristics(), 0x40000040);

    const auto sectionBytes = modified.binary().part(insertedSection->rawAddress().get(), insertedSection->rawSize());
    ASSERT_EQ(sectionBytes, byte_vec(insertedSection->rawSize(), 0x00));
    ASSERT_EQ(modified.sectionCount(), originalSectionCount + 1);
}

TEST(PeFormatTest, CanAddNewSectionsIn64Bit)
{
    constexpr binary_offset SECTION_SIZE = 0x10001;
    const auto permissions = CSectionPermissions { SectionPermissionType::EXECUTE };
    auto modified = x86_64exe->addPeSection(".test_d", SECTION_SIZE, permissions);
    const auto originalSectionCount = x86_64exe->sectionCount();

    auto originalSections = x86_64exe->peSections();
    auto modifiedSections = modified.peSections();
    const auto insertedSection = modifiedSections.back();

    ASSERT_EQ(modifiedSections.size(), originalSections.size() + 1);
    ASSERT_EQ(modified.binary().size(), x86_64exe->binary().size() + insertedSection->rawSize());

    ASSERT_STREQ(insertedSection->name().c_str(), ".test_d");
    ASSERT_EQ(insertedSection->virtualSize(), SECTION_SIZE);
    ASSERT_GE(insertedSection->rawSize(), SECTION_SIZE);
    ASSERT_EQ(insertedSection->permissions(), permissions);
    ASSERT_EQ(insertedSection->characteristics(), 0x60000020);

    const auto sectionBytes = modified.binary().part(insertedSection->rawAddress().get(), insertedSection->rawSize());
    ASSERT_EQ(sectionBytes, byte_vec(insertedSection->rawSize(), 0x00));
    ASSERT_EQ(modified.sectionCount(), originalSectionCount + 1);
}

