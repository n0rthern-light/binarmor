#include <gtest/gtest.h>
#include "../BinaryMother.hpp"
#include "core/application/container.hpp"
#include "core/application/behave.hpp"
#include "core/format/pe/defines.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "core/shared/SectionPermissions.hpp"
#include "shared/application/container.hpp"
#include "shared/value/ByteVecOperations.hpp"
#include "shared/value/Uuid.hpp"
#include <memory>
#include <optional>
#include <stdio.h>
#include <unistd.h>

using namespace program::core::modification::bytes;

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
        std::make_shared<CAddBytesCommand>(
            fileId,
            CUuid{ },
            std::nullopt,
            byte_vec { 0xDE, 0xDB, 0xEE, 0xFF, 0x01, 0x05, 0x00, 0xCC }
        )
    );

    //then-pre
    auto pe = binaryFile->modifiedBinaryAsFormat();
    auto sections = pe->sections();

    auto testedSection = sections.back();
    ASSERT_STREQ(testedSection->name().c_str(), ".bnrmr");
    ASSERT_FALSE(testedSection->permissions().hasPermissionTo(SectionPermissionType::WRITE));
    ASSERT_FALSE(testedSection->permissions().hasPermissionTo(SectionPermissionType::EXECUTE));
    const auto partActual0 = pe->binary().part(testedSection->baseAddress().get(), sectionSize);
    auto partExpected0 = byte_vec { 0xDE, 0xDB, 0xEE, 0xFF, 0x01, 0x05, 0x00, 0xCC, };
    partExpected0 = CByteVecOperations::bytesAppendToEnd(partExpected0, byte_vec(sectionSize - partExpected0.size(), PE_SECTION_NULL_BYTE));
    ASSERT_EQ(partActual0, partExpected0);

    //when-continue
    program::shared::container::commandBus->publish(
        std::make_shared<CAddBytesCommand>(
            fileId,
            CUuid{ },
            ".xonw",
            byte_vec { 0xE8, 0x90, 0x01, 0x90, 0xDB, 0x95, 0xFF },
            true
        )
    );

    program::shared::container::commandBus->publish(
        std::make_shared<CAddBytesCommand>(
            fileId,
            CUuid{ },
            std::nullopt,
            byte_vec { 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A }
        )
    );

    //then
    pe = binaryFile->modifiedBinaryAsFormat();
    sections = pe->sections();

    testedSection = sections.back();
    ASSERT_STREQ(testedSection->name().c_str(), ".xonw");
    ASSERT_FALSE(testedSection->permissions().hasPermissionTo(SectionPermissionType::WRITE));
    ASSERT_TRUE(testedSection->permissions().hasPermissionTo(SectionPermissionType::EXECUTE));
    const auto partActual = pe->binary().part(testedSection->baseAddress().get(), sectionSize);
    auto partExpected = byte_vec { 0xE8, 0x90, 0x01, 0x90, 0xDB, 0x95, 0xFF };
    partExpected = CByteVecOperations::bytesAppendToEnd(partExpected, byte_vec(sectionSize - partExpected.size(), PE_SECTION_NULL_BYTE));
    ASSERT_EQ(partActual, partExpected);

    testedSection = sections[sections.size() - 2];
    ASSERT_STREQ(testedSection->name().c_str(), ".bnrmr");
    ASSERT_FALSE(testedSection->permissions().hasPermissionTo(SectionPermissionType::WRITE));
    ASSERT_FALSE(testedSection->permissions().hasPermissionTo(SectionPermissionType::EXECUTE));
    const auto partActual2 = pe->binary().part(testedSection->baseAddress().get(), sectionSize);
    auto partExpected2 = byte_vec { 0xDE, 0xDB, 0xEE, 0xFF, 0x01, 0x05, 0x00, 0xCC, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A };
    partExpected2 = CByteVecOperations::bytesAppendToEnd(partExpected2, byte_vec(sectionSize - partExpected2.size(), PE_SECTION_NULL_BYTE));
    ASSERT_EQ(partActual2, partExpected2);
}

INSTANTIATE_TEST_SUITE_P(
    AddBytesHandlerMultipleFilesTest,
    AddBytesHandlerTest,
    ::testing::Values("/windows/x86.dll", "/windows/x86.exe", "/windows/x86_64.dll", "/windows/x86_64.exe")
);
