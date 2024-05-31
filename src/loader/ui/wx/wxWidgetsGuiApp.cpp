#include "wxWidgetsGuiApp.hpp"
#include "shared/message/IMessageBus.hpp"

CwxWidgetsGuiApp::CwxWidgetsGuiApp(int _argc, char** _argv, IMessageBus* t_eventBus)
{
    argc = _argc;
    argv = _argv;
    m_eventBus = t_eventBus;

    app = new CwxApp();
    wxApp::SetInstance(app);
    app->CallOnInit();
    frame = new CwxFrame(m_eventBus);
}

void CwxWidgetsGuiApp::start()
{
    wxEntryStart(argc, argv);
    frame->Show(true);
    app->OnRun();
    app->OnExit();
    wxEntryCleanup();
}

void CwxWidgetsGuiApp::promptOpenFile()
{
    frame->promptOpenFile();
}

void CwxWidgetsGuiApp::displayErrorMessageBox(const std::string& title, const std::string& message)
{
    wxMessageBox(message, title, wxICON_ERROR | wxOK);
}

void CwxWidgetsGuiApp::displayInfoMessageBox(const std::string& title, const std::string& message)
{
    wxMessageBox(message, title);
}

void CwxWidgetsGuiApp::displayStatus(const std::string& statusText)
{
    frame->displayStatus(statusText);
}

void CwxWidgetsGuiApp::displayBinaryFile(const CBinaryFile& binaryFile)
{
    frame->displayBinaryFile(binaryFile);
}

void CwxWidgetsGuiApp::exit()
{
    app->Exit();
}

