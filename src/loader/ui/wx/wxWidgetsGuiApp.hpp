#pragma once

#include "../IGuiApp.hpp"
#include "wxApp.hpp"
#include "wxFrame.hpp"
#include <shared/event/IEventBus.hpp>

class CwxWidgetsGuiApp : public IGuiApp
{
	int argc;
	char** argv;
	IEventBus* eventBus;
	CwxApp* app;
	CwxFrame* frame;

public:
	CwxWidgetsGuiApp(int _argc, char** _argv, IEventBus* _eventBus);
	void start();
	void promptOpenFile();
	void displayStatus(const std::string& statusText);
	void displayBinary(const CBinary& binary);
	void exit();
};

