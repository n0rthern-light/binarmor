#ifndef LOADER_UI_WX_WX_FRAME_HPP_
#define LOADER_UI_WX_WX_FRAME_HPP_

#include "wxContentPanel.hpp"
#include "wxSidebarPanel.hpp"
#include <shared/message/IMessageBus.hpp>
#include <core/file/BinaryFile.hpp>
#include <wx/event.h>

class CwxFrame : public wxFrame
{
private:
    program::shared::message::IMessageBus* m_eventBus;
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
    CwxFrame(program::shared::message::IMessageBus* t_eventBus);
    void promptOpenFile();
    void displayStatus(const std::string& statusText);
    void highlightBinaryFileInList(const program::core::file::file_id& fileId);
    void removeFromFileList(const program::core::file::file_id& fileId);
    void displayBinaryFile(const program::core::file::CBinaryFile& binaryFile);
    void appendToLoadedFiles(const program::core::file::CBinaryFile* binary);
    void displayEmpty();
    void notifyAboutNewFile(const std::string& path);
};

#endif // LOADER_UI_WX_WX_FRAME_HPP_
