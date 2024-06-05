#include "container.hpp"
#include <shared/application/container.hpp>
#include "../file/fstream/fstreamFileReader.hpp"

std::unique_ptr<IFileReader> program::core::container::file::fileReader = nullptr;
std::unique_ptr<CBinaryFileStateManager> program::core::container::file::binaryFileStateManager = nullptr;
std::unique_ptr<CAnalysisRunner> program::core::container::file::analysis::runner = nullptr;

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
}

