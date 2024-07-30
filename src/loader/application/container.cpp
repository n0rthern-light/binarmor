#include "container.hpp"
#include "../ui/wx/wxWidgetsGuiApp.hpp"
#include <shared/application/container.hpp>

IGuiApp* program::loader::container::guiApp = nullptr;

void program::loader::container::init(int argc, char** argv)
{
    program::loader::container::guiApp = new CwxWidgetsGuiApp(argc, argv, program::shared::container::eventBus.get());
}

void program::loader::container::exit()
{
    program::loader::container::guiApp->exit();
    delete program::loader::container::guiApp;
    program::loader::container::guiApp = nullptr;
}
