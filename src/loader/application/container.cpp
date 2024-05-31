#include "container.hpp"
#include "../ui/wx/wxWidgetsGuiApp.hpp"
#include <shared/application/container.hpp>

std::shared_ptr<IGuiApp> program::loader::container::guiApp = nullptr;

void program::loader::container::init(int argc, char** argv)
{
    program::loader::container::guiApp = std::make_shared<CwxWidgetsGuiApp>(argc, argv, program::shared::container::eventBus.get());
}

