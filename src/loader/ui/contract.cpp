#include "contract.hpp"
#include "wx/CWxWidgetsGuiApp.hpp"

std::shared_ptr<IGuiApp> ui::guiApp = nullptr;

void ui::init(int argc, char** argv)
{
	ui::guiApp = std::make_shared<CWxWidgetsGuiApp>(argc, argv);
}

