#pragma once

#include "../IGuiApp.hpp"
#include "wxApp.hpp"
#include "wxFrame.hpp"

class CwxWidgetsGuiApp : public IGuiApp
{
	CwxApp* app;
	CwxFrame* frame;

public:
	CwxWidgetsGuiApp(int argc, char** argv);
};

