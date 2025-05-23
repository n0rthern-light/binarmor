#ifndef LOADER_UI_WX_WX_WIDGETS_GUI_APP_HPP_
#define LOADER_UI_WX_WX_WIDGETS_GUI_APP_HPP_

#include "../IGuiApp.hpp"
#include "wxFrame.hpp"
#include "wxApp.hpp"
#include <shared/message/IMessageBus.hpp>
#include <core/file/BinaryFile.hpp>

class CwxWidgetsGuiApp : public CwxApp, public IGuiApp
{
    int m_argc;
    char** m_argv;
    IMessageBus* m_eventBus;
    CwxFrame* m_frame;

public:
    CwxWidgetsGuiApp(int t_argc, char** t_argv, IMessageBus* t_eventBus);
    void overrideEventBusHandlerType();
    void start();
    void promptOpenFile();
    void displayErrorMessageBox(const std::string& title, const std::string& message);
    void displayInfoMessageBox(const std::string& title, const std::string& message);
    void displayStatus(const std::string& statusText);
    void highlightBinaryInFileList(const file_id& fileId);
    void removeFromFileList(const file_id& fileId);
    void displayBinaryFile(const CBinaryFile& binaryFile);
    void appendToLoadedFiles(const CBinaryFile* binary);
    void displayEmpty();
    void exit();
};

#endif // LOADER_UI_WX_WX_WIDGETS_GUI_APP_HPP_
