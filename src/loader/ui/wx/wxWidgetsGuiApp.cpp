#include "wxWidgetsGuiApp.hpp"
#include "shared/message/simple/SimpleMessageBus.hpp"
#include <shared/message/IMessageBus.hpp>

using namespace program::core::file;

CwxWidgetsGuiApp::CwxWidgetsGuiApp(int t_argc, char** t_argv, IMessageBus* t_eventBus)
{
    m_argc = t_argc;
    m_argv = t_argv;
    m_eventBus = t_eventBus;

    wxApp::SetInstance(this);
    CallOnInit();
    m_frame = new CwxFrame(m_eventBus);

    //overrideEventBusHandlerType();
}

void CwxWidgetsGuiApp::overrideEventBusHandlerType()
{
    // this should be a better way of handling but it crashes the app
    // so just use regular sync handler type atm
    dynamic_cast<CSimpleMessageBus*>(m_eventBus)
        ->overrideHandlerType([&](handler_type_fn f) {
            CallAfter(f);
        });
}

void CwxWidgetsGuiApp::start()
{
    wxEntryStart(m_argc, m_argv);
    m_frame->Show(true);
    OnRun();
    OnExit();
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

void CwxWidgetsGuiApp::highlightBinaryInFileList(const file_id& fileId)
{
    m_frame->highlightBinaryFileInList(fileId);
}

void CwxWidgetsGuiApp::removeFromFileList(const file_id& fileId)
{
    m_frame->removeFromFileList(fileId);
}

void CwxWidgetsGuiApp::displayBinaryFile(const CBinaryFile& binaryFile)
{
    m_frame->displayBinaryFile(binaryFile);
}

void CwxWidgetsGuiApp::appendToLoadedFiles(const CBinaryFile* binary)
{
    m_frame->appendToLoadedFiles(binary);
}

void CwxWidgetsGuiApp::displayEmpty()
{
    m_frame->displayEmpty();
}

void CwxWidgetsGuiApp::exit()
{
    m_frame->Close(true);
}

