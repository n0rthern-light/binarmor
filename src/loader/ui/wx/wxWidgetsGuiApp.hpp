#pragma once

#include "../IGuiApp.hpp"
#include "wxApp.hpp"
#include "wxFrame.hpp"
#include <shared/event/IEventBus.hpp>

class CwxWidgetsGuiApp : public IGuiApp
{
	IEventBus* eventBus;
	CwxApp* app;
	CwxFrame* frame;

public:
	CwxWidgetsGuiApp(int argc, char** argv);
	void exit();
};

