#include "container.hpp"
#include <shared/application/container.hpp>
#include "../file/fstream/fstreamFileReader.hpp"

std::shared_ptr<IFileReader> program::core::container::file::fileReader = nullptr;
std::shared_ptr<CBinaryFileStateManager> program::core::container::file::binaryFileStateManager = nullptr;
std::shared_ptr<CAnalysisRunner> program::core::container::file::analysis::runner = nullptr;

void program::core::container::init(int argc, char** argv)
{
    program::core::container::file::fileReader = std::make_shared<CfstreamFileReader>();
    program::core::container::file::binaryFileStateManager = std::make_shared<CBinaryFileStateManager>(program::shared::container::eventBus.get(), program::core::container::file::fileReader.get());
    program::core::container::file::analysis::runner = std::make_shared<CAnalysisRunner>(program::shared::container::eventBus.get());
}

