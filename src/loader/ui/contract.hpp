#pragma once

#include "IGuiApp.hpp"

namespace ui {
	extern std::shared_ptr<IGuiApp> guiApp;

	void init(int argc, char** argv);
}

