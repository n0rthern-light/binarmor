#include <gtest/gtest.h>
#include "../BinaryMother.hpp"
#include "core/application/container.hpp"
#include "core/application/behave.hpp"
#include "core/format/pe/PeFormat.hpp"
#include "core/format/pe/defines.hpp"
#include "core/modification/AddSectionCommand.hpp"
#include "core/shared/SectionPermissions.hpp"
#include "shared/application/container.hpp"
#include <memory>
#include <stdio.h>
#include <unistd.h>

class AddSectionHandlerTest : public ::testing::TestWithParam<std::string> {
};

TEST_P(AddSectionHandlerTest, CanAddSection)
{
    //given
    program::shared::container::init(0, nullptr);
    program::core::container::init(0, nullptr);
    program::core::application::behave(0, nullptr);
    program::core::container::file::binaryFileStateManager->load(BinaryMother::testBinaryPath(GetParam()));
    const auto fileId = program::core::container::file::binaryFileStateManager->loadedFiles()[0];
    const auto originalSize = program::core::container::file::binaryFileStateManager->binaryFile(fileId)->originalBinary().size();

    //when
    program::shared::container::commandBus->publish(
        std::make_shared<CAddSectionCommand>(
            fileId,
            ".zxcvbx",
            CSectionPermissions{ SectionPermissionType::EXECUTE },
            1000
        )
    );
    program::shared::container::commandBus->publish(
        std::make_shared<CAddSectionCommand>(
            fileId,
            ".zxcvbd",
            CSectionPermissions{ SectionPermissionType::WRITE },
            1000
        )
    );
    //sleep(1);

    //then
    auto pe = CPeFormat { program::core::container::file::binaryFileStateManager->binaryFileModifiedBinary(fileId) };
    auto sections = pe.peSections();

    ASSERT_STREQ(sections.back()->name().c_str(), ".zxcvbd");
    ASSERT_TRUE(sections.back()->permissions().hasPermissionTo(SectionPermissionType::WRITE));
    ASSERT_EQ(pe.binary().part(sections.back()->rawAddress().get(), sections.back()->rawSize()), byte_vec(sections.back()->rawSize(), PE_SECTION_NULL_BYTE));

    ASSERT_STREQ(sections[sections.size() - 2]->name().c_str(), ".zxcvbx");
    ASSERT_TRUE(sections[sections.size() - 2]->permissions().hasPermissionTo(SectionPermissionType::EXECUTE));
    ASSERT_EQ(pe.binary().part(sections[sections.size() - 2]->rawAddress().get(), sections[sections.size() - 2]->rawSize()), byte_vec(sections[sections.size() - 2]->rawSize(), PE_SECTION_NULL_BYTE));

    const auto finalSize = program::core::container::file::binaryFileStateManager->binaryFile(fileId)->modifiedBinary().size();
    ASSERT_EQ(finalSize, originalSize + 2048);
}

INSTANTIATE_TEST_SUITE_P(
    AddSectionHandlerMultipleFilesTest,
    AddSectionHandlerTest,
    ::testing::Values("/windows/x86.dll", "/windows/x86.exe", "/windows/x86_64.dll", "/windows/x86_64.exe")
);

