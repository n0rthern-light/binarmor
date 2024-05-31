#pragma once

#include "../IGuiApp.hpp"
#include "wxApp.hpp"
#include "wxFrame.hpp"
#include <shared/message/IMessageBus.hpp>
#include <core/file/BinaryFile.hpp>

class CwxWidgetsGuiApp : public IGuiApp
{
	int m_argc;
	char** m_argv;
	IMessageBus* m_eventBus;
    CwxApp* m_app;
    CwxFrame* m_frame;

public:
	CwxWidgetsGuiApp(int t_argc, char** t_argv, IMessageBus* t_eventBus);
	void start();
    void promptOpenFile();
	void displayErrorMessageBox(const std::string& title, const std::string& message);
	void displayInfoMessageBox(const std::string& title, const std::string& message);
	void displayStatus(const std::string& statusText);
	void displayBinaryFile(const CBinaryFile& binaryFile);
    void unlockFeatures();
    void lockFeatures();
	void exit();
};

