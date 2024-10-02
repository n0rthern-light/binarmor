#include <gtest/gtest.h>
#include "../BinaryMother.hpp"
#include "core/application/container.hpp"
#include "core/application/behave.hpp"
#include "core/format/IFormat.hpp"
#include "core/format/pe/PeFormat.hpp"
#include "core/format/pe/defines.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "core/modification/AddImportCommand.hpp"
#include "core/shared/SectionPermissions.hpp"
#include "shared/application/container.hpp"
#include "shared/value/ByteVecOperations.hpp"
#include "shared/value/Uuid.hpp"
#include <memory>
#include <stdio.h>
#include <unistd.h>

class AddImportHandlerTest : public ::testing::TestWithParam<std::string> {
};

TEST_P(AddImportHandlerTest, CanAddImport)
{
    //given
    program::shared::container::init(0, nullptr);
    program::core::container::init(0, nullptr);
    program::core::application::behave(0, nullptr);
    program::core::container::file::binaryFileStateManager->load(BinaryMother::testBinaryPath(GetParam()));
    const auto fileId = program::core::container::file::binaryFileStateManager->loadedFiles()[0];
    const CUuid bytesId { };
    const auto sectionSize = 512;
    const auto binaryFile = program::core::container::file::binaryFileStateManager->binaryFile(fileId);

    //when
    program::shared::container::commandBus->publish(
        std::make_shared<CAddImportCommand>(
            fileId,
            "ntdll.dll",
            "NtRaiseHardError"
        )
    );

    //then
    const auto format = binaryFile->modifiedBinaryAsFormat();
    const auto& importModules = format->importModules();

    ASSERT_TRUE(importModules.find("KERNEL32.dll") != importModules.end());
    ASSERT_TRUE(importModules.find("ntdll.dll") != importModules.end());
}

INSTANTIATE_TEST_SUITE_P(
    AddImportHandlerMultipleFilesTest,
    AddImportHandlerTest,
    ::testing::Values("/windows/x86.dll", "/windows/x86.exe", "/windows/x86_64.dll", "/windows/x86_64.exe")
);
