#include "contract.hpp"
#include "wx/wxWidgetsGuiApp.hpp"

std::shared_ptr<IGuiApp> ui::guiApp = nullptr;

void ui::init(int argc, char** argv)
{
	ui::guiApp = std::make_shared<CwxWidgetsGuiApp>(argc, argv);
}
