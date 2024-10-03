#include <gtest/gtest.h>
#include "../BinaryMother.hpp"
#include "core/application/container.hpp"
#include "core/application/behave.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/format/IFormat.hpp"
#include "core/format/pe/PeFormat.hpp"
#include "core/format/pe/defines.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "core/modification/ChangeBytesCommand.hpp"
#include "core/shared/SectionPermissions.hpp"
#include "shared/application/container.hpp"
#include "shared/value/ByteVecOperations.hpp"
#include "shared/value/Uuid.hpp"
#include <memory>
#include <optional>
#include <stdio.h>
#include <unistd.h>

class AddBytesHandlerTest : public ::testing::TestWithParam<std::string> {
};

TEST_P(AddBytesHandlerTest, CanAddBytes)
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
        std::make_shared<CChangeBytesCommand>(
            fileId,
            CUuid{ },
            100,
            byte_vec { 0xDE, 0xDB, 0xEE, 0xFF, 0x01, 0x05, 0x00, 0xCC },
            BinaryModificationType::ENCRYPT_DATA
        )
    );

    //then
    auto fmt = binaryFile->modifiedBinaryAsFormat();
    auto bytes = fmt->binary().part(100, 8).bytes();

    ASSERT_EQ(bytes, (byte_vec { 0xDE, 0xDB, 0xEE, 0xFF, 0x01, 0x05, 0x00, 0xCC }));
}

INSTANTIATE_TEST_SUITE_P(
    AddBytesHandlerMultipleFilesTest,
    AddBytesHandlerTest,
    ::testing::Values("/windows/x86.dll", "/windows/x86.exe", "/windows/x86_64.dll", "/windows/x86_64.exe")
);
