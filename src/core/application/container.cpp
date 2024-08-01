#include "container.hpp"
#include <memory>
#include <shared/application/container.hpp>
#include "../file/fstream/fstreamFileReader.hpp"
#include "../assembler/asmjit/AsmJitAssembler.hpp"
#include "core/modification/bytes/AddBytesHandler.hpp"
#include "core/modification/section/AddSectionHandler.hpp"

std::unique_ptr<IFileReader> program::core::container::file::fileReader = nullptr;
std::unique_ptr<CBinaryFileStateManager> program::core::container::file::binaryFileStateManager = nullptr;
std::unique_ptr<CAnalysisRunner> program::core::container::file::analysis::runner = nullptr;
std::unique_ptr<IAssembler> program::core::container::assembly::assembler = nullptr;
std::unique_ptr<CAddSectionHandler> program::core::container::handler::addSectionHandler = nullptr;
std::unique_ptr<CAddBytesHandler> program::core::container::handler::addBytesHandler = nullptr;

void program::core::container::init(int argc, char** argv)
{
    program::core::container::file::fileReader = std::make_unique<CfstreamFileReader>();
    program::core::container::file::analysis::runner = std::make_unique<CAnalysisRunner>(
        program::shared::container::eventBus.get(),
        program::shared::container::hasher.get()
    );
    program::core::container::file::binaryFileStateManager = std::make_unique<CBinaryFileStateManager>(
        program::shared::container::eventBus.get(),
        program::core::container::file::fileReader.get(),
        program::core::container::file::analysis::runner.get()
    );
    program::core::container::assembly::assembler = std::make_unique<CAsmJitAssembler>();
    program::core::container::handler::addSectionHandler = std::make_unique<CAddSectionHandler>(
        program::core::container::file::binaryFileStateManager.get()
    );
    program::core::container::handler::addBytesHandler = std::make_unique<CAddBytesHandler>(
        program::shared::container::commandBus.get(),
        program::core::container::file::binaryFileStateManager.get()
    );
}

void program::core::container::exit()
{
    program::core::container::assembly::assembler = nullptr;
    program::core::container::file::binaryFileStateManager = nullptr;
    program::core::container::file::analysis::runner = nullptr;
    program::core::container::file::fileReader = nullptr;
    program::core::container::handler::addSectionHandler = nullptr;
    program::core::container::handler::addBytesHandler = nullptr;
}
