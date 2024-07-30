#include <gtest/gtest.h>
#include "../BinaryMother.hpp"
#include "core/application/container.hpp"
#include "core/application/behave.hpp"
#include "core/format/pe/PeFormat.hpp"
#include "core/modification/AddSectionCommand.hpp"
#include "core/shared/SectionPermissions.hpp"
#include "shared/application/container.hpp"
#include <memory>
#include <stdio.h>
#include <unistd.h>

TEST(AddSectionHandlerTest, CanAddSectionToX86)
{
    //given
    program::shared::container::init(0, nullptr);
    program::core::container::init(0, nullptr);
    program::core::application::behave(0, nullptr);
    program::core::container::file::binaryFileStateManager->load(BinaryMother::testBinaryPath("/windows/x86.dll"));
    const auto fileId = program::core::container::file::binaryFileStateManager->loadedFiles()[0];

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

    ASSERT_STREQ(sections[sections.size() - 2]->name().c_str(), ".zxcvbx");
    ASSERT_TRUE(sections[sections.size() - 2]->permissions().hasPermissionTo(SectionPermissionType::EXECUTE));
}

TEST(AddSectionHandlerTest, CanAddSectionToX64)
{
    //given
    program::shared::container::init(0, nullptr);
    program::core::container::init(0, nullptr);
    program::core::application::behave(0, nullptr);
    program::core::container::file::binaryFileStateManager->load(BinaryMother::testBinaryPath("/windows/x86_64.exe"));
    const auto fileId = program::core::container::file::binaryFileStateManager->loadedFiles()[0];

    //when
    program::shared::container::commandBus->publish(
        std::make_shared<CAddSectionCommand>(
            fileId,
            "._1",
            CSectionPermissions{ SectionPermissionType::EXECUTE },
            1000
        )
    );
    program::shared::container::commandBus->publish(
        std::make_shared<CAddSectionCommand>(
            fileId,
            "._2",
            CSectionPermissions{ SectionPermissionType::WRITE },
            1000
        )
    );
    //sleep(1);

    //then
    auto pe = CPeFormat { program::core::container::file::binaryFileStateManager->binaryFileModifiedBinary(fileId) };
    auto sections = pe.peSections();

    ASSERT_STREQ(sections.back()->name().c_str(), "._2");
    ASSERT_TRUE(sections.back()->permissions().hasPermissionTo(SectionPermissionType::WRITE));

    ASSERT_STREQ(sections[sections.size() - 2]->name().c_str(), "._1");
    ASSERT_TRUE(sections[sections.size() - 2]->permissions().hasPermissionTo(SectionPermissionType::EXECUTE));
}

