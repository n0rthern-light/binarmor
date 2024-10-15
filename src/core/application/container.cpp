#include "container.hpp"
#include <memory>
#include <shared/application/container.hpp>
#include "../file/fstream/fstreamFileReader.hpp"
#include "../assembler/keystone/KeystoneAssembler.hpp"
#include "core/modification/bytes/AddBytesHandler.hpp"
#include "core/modification/bytes/ChangeBytesHandler.hpp"
#include "core/modification/import/AddImportsHandler.hpp"
#include "core/modification/import/EncryptOriginalImportsHandler.hpp"
#include "core/modification/resize/FixBinaryResizeHandler.hpp"
#include "core/modification/section/AddSectionHandler.hpp"
#include "core/modification/section/InitializeMainProtectionSectionHandler.hpp"
#include "core/payload/processor/NasmPayloadProcessor.hpp"
#include "core/shared/attributes.hpp"

std::unique_ptr<program::core::file::IFileSystem> program::core::container::file::fileSystem = nullptr;
std::unique_ptr<program::core::file::CBinaryFileStateManager> program::core::container::file::binaryFileStateManager = nullptr;
std::unique_ptr<program::core::analysis::CAnalysisRunner> program::core::container::file::analysis::runner = nullptr;
std::unique_ptr<program::core::assembler::IAssembler> program::core::container::assembly::assembler_x86 = nullptr;
std::unique_ptr<program::core::assembler::IAssembler> program::core::container::assembly::assembler_x86_64 = nullptr;
std::unique_ptr<program::core::assembler::IAssembler> program::core::container::assembly::assembler_arm64 = nullptr;
std::unique_ptr<program::core::payload::IPayloadProcessor> program::core::container::payload::payloadProcessor = nullptr;
std::unique_ptr<program::core::modification::section::CAddSectionHandler> program::core::container::handler::addSectionHandler = nullptr;
std::unique_ptr<program::core::modification::bytes::CAddBytesHandler> program::core::container::handler::addBytesHandler = nullptr;
std::unique_ptr<program::core::modification::bytes::CChangeBytesHandler> program::core::container::handler::changeBytesHandler = nullptr;
std::unique_ptr<program::core::modification::import::CAddImportsHandler> program::core::container::handler::addImportsHandler = nullptr;
std::unique_ptr<program::core::modification::encrypt::CEncryptOriginalImportsHandler> program::core::container::handler::encryptOriginalImportsHandler = nullptr;
std::unique_ptr<program::core::modification::section::CInitializeMainProtectionSectionHandler> program::core::container::handler::initializeMainProtectionSectionHandler = nullptr;
std::unique_ptr<program::core::modification::resize::CFixBinaryResizeHandler> program::core::container::handler::fixBinaryResizeHandler = nullptr;

void program::core::container::init(int argc, char** argv)
{
    program::core::container::file::fileSystem = std::make_unique<program::core::file::fstream::CfstreamFileSystem>();
    program::core::container::file::analysis::runner = std::make_unique<program::core::analysis::CAnalysisRunner>(
        program::shared::container::eventBus.get(),
        program::shared::container::hasher.get()
    );
    program::core::container::file::binaryFileStateManager = std::make_unique<program::core::file::CBinaryFileStateManager>(
        program::shared::container::eventBus.get(),
        program::core::container::file::fileSystem.get(),
        program::core::container::file::analysis::runner.get()
    );
    program::core::container::assembly::assembler_x86 = std::make_unique<program::core::assembler::keystone::CKeystoneAssembler>(Architecture::X86, Endianness::LITTLE);
    program::core::container::assembly::assembler_x86_64 = std::make_unique<program::core::assembler::keystone::CKeystoneAssembler>(Architecture::X86_64, Endianness::LITTLE);
    program::core::container::assembly::assembler_arm64 = std::make_unique<program::core::assembler::keystone::CKeystoneAssembler>(Architecture::ARM64, Endianness::LITTLE);
    program::core::container::payload::payloadProcessor = std::make_unique<program::core::payload::nasm::CNasmPayloadProcessor>(
        program::core::container::file::binaryFileStateManager.get()
    );
    program::core::container::handler::addSectionHandler = std::make_unique<program::core::modification::section::CAddSectionHandler>(
        program::core::container::file::binaryFileStateManager.get()
    );
    program::core::container::handler::addBytesHandler = std::make_unique<program::core::modification::bytes::CAddBytesHandler>(
        program::shared::container::commandBus.get(),
        program::core::container::file::binaryFileStateManager.get()
    );
    program::core::container::handler::changeBytesHandler = std::make_unique<program::core::modification::bytes::CChangeBytesHandler>(
        program::core::container::file::binaryFileStateManager.get()
    );
    program::core::container::handler::addImportsHandler = std::make_unique<program::core::modification::import::CAddImportsHandler>(
        program::core::container::file::binaryFileStateManager.get(),
        program::shared::container::crypter.get(),
        program::shared::container::commandBus.get()
    );
    program::core::container::handler::encryptOriginalImportsHandler = std::make_unique<program::core::modification::encrypt::CEncryptOriginalImportsHandler>(
        program::core::container::file::binaryFileStateManager.get(),
        program::shared::container::crypter.get()
    );
    program::core::container::handler::initializeMainProtectionSectionHandler = std::make_unique<program::core::modification::section::CInitializeMainProtectionSectionHandler>(
        program::shared::container::commandBus.get(),
        program::core::container::file::binaryFileStateManager.get()
    );

    program::core::container::handler::fixBinaryResizeHandler = std::make_unique<program::core::modification::resize::CFixBinaryResizeHandler>(
        program::core::container::file::binaryFileStateManager.get()
    );

}

void program::core::container::exit()
{
    program::core::container::assembly::assembler_x86 = nullptr;
    program::core::container::assembly::assembler_x86_64 = nullptr;
    program::core::container::assembly::assembler_arm64 = nullptr;
    program::core::container::file::binaryFileStateManager = nullptr;
    program::core::container::file::analysis::runner = nullptr;
    program::core::container::file::fileSystem = nullptr;
    program::core::container::payload::payloadProcessor = nullptr;
    program::core::container::handler::addSectionHandler = nullptr;
    program::core::container::handler::addBytesHandler = nullptr;
    program::core::container::handler::changeBytesHandler = nullptr;
    program::core::container::handler::encryptOriginalImportsHandler = nullptr;
    program::core::container::handler::addImportsHandler = nullptr;
    program::core::container::handler::initializeMainProtectionSectionHandler = nullptr;
    program::core::container::handler::fixBinaryResizeHandler  = nullptr;
}
