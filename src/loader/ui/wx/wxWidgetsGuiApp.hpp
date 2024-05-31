#pragma once

#include "../IGuiApp.hpp"
#include "wxApp.hpp"
#include "wxFrame.hpp"
#include <shared/message/IMessageBus.hpp>
#include <core/file/BinaryFile.hpp>

class CwxWidgetsGuiApp : public IGuiApp
{
	int argc;
	char** argv;
	IMessageBus* eventBus;
	CwxApp* app;
	CwxFrame* frame;

public:
	CwxWidgetsGuiApp(int _argc, char** _argv, IMessageBus* _eventBus);
	void start();
	void promptOpenFile();
	void displayErrorMessageBox(const std::string& title, const std::string& message);
	void displayInfoMessageBox(const std::string& title, const std::string& message);
	void displayStatus(const std::string& statusText);
	void displayBinaryFile(const CBinaryFile& binaryFile);
	void exit();
};

