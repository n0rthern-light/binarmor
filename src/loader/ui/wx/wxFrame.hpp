#ifndef LOADER_UI_WX_WX_FRAME_HPP_
#define LOADER_UI_WX_WX_FRAME_HPP_

#include "wxContentPanel.hpp"
#include "wxSidebarPanel.hpp"
#include <shared/message/IMessageBus.hpp>
#include <core/file/BinaryFile.hpp>

class CwxFrame : public wxFrame
{
private:
    IMessageBus* m_eventBus;
    wxPanel* m_mainPanel;
    wxBoxSizer* m_mainSizer;
    CwxSidebarPanel* m_sidebarPanel;
    CwxContentPanel* m_contentPanel;

    void initUi();
    void initEventListener();
    void initThreads();
    void initFileDrop();
    void onEventDisplayWindowOpenFile(wxCommandEvent& event);
public:
    CwxFrame(IMessageBus* t_eventBus);
    void promptOpenFile();
    void displayStatus(const std::string& statusText);
    void highlightBinaryFileInList(const file_id& fileId);
    void removeFromFileList(const file_id& fileId);
    void displayBinaryFile(const CBinaryFile& binaryFile);
    void appendToLoadedFiles(const CBinaryFile* binary);
    void displayEmpty();
    void notifyAboutNewFile(const std::string& path);
};

#endif // LOADER_UI_WX_WX_FRAME_HPP_
