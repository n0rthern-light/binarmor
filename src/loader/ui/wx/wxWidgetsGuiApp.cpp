#include "wxWidgetsGuiApp.hpp"
#include "shared/message/IMessageBus.hpp"

CwxWidgetsGuiApp::CwxWidgetsGuiApp(int t_argc, char** t_argv, IMessageBus* t_eventBus)
{
    m_argc = t_argc;
    m_argv = t_argv;
    m_eventBus = t_eventBus;

    m_app = new CwxApp();
    wxApp::SetInstance(m_app);
    m_app->CallOnInit();
    m_frame = new CwxFrame(m_eventBus);
}

void CwxWidgetsGuiApp::start()
{
    wxEntryStart(m_argc, m_argv);
    m_frame->Show(true);
    m_app->OnRun();
    m_app->OnExit();
    wxEntryCleanup();
}

void CwxWidgetsGuiApp::promptOpenFile()
{
    m_frame->promptOpenFile();
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
    m_frame->displayStatus(statusText);
}

void CwxWidgetsGuiApp::displayBinaryFile(const CBinaryFile& binaryFile)
{
    m_frame->displayBinaryFile(binaryFile);
}

void CwxWidgetsGuiApp::lockFeatures()
{
    m_frame->lockFeatures();
}

void CwxWidgetsGuiApp::unlockFeatures()
{
    m_frame->unlockFeatures();
}

void CwxWidgetsGuiApp::exit()
{
    m_app->Exit();
}

