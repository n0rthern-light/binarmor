#include <gtest/gtest.h>
#include "../../BinaryMother.hpp"
#include "core/shared/SectionPermissions.hpp"
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

TEST(PeSectionTest, CanAddNewSections)
{
    auto modified = x86exe->addSection(".test_d", 0x10000, CSectionPermissions { SectionPermissionType::WRITE })
        .addSection(".test_x", 0x10000, CSectionPermissions { SectionPermissionType::EXECUTE });

    auto originalSections = x86exe->sections();
    auto modifiedSections = modified.sections();

    //ASSERT_EQ(modifiedSections.size(), originalSections.size() + 2);
    ASSERT_EQ(x86exe->binary().size(), modified.binary().size());
}

