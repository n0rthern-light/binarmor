#ifndef LOADER_UI_WX_WX_FRAME_HPP_
#define LOADER_UI_WX_WX_FRAME_HPP_

#include "loader/ui/wx/wxContentPanel.hpp"
#include "loader/ui/wx/wxSidebarPanel.hpp"
#include <shared/message/IMessageBus.hpp>
#include <core/file/BinaryFile.hpp>

class CwxFrame : public wxFrame
{
private:
    IMessageBus* m_eventBus;
    std::unique_ptr<wxPanel> m_mainPanel;
    std::unique_ptr<wxBoxSizer> m_mainSizer;
    std::unique_ptr<CwxSidebarPanel> m_sidebarPanel;
    std::unique_ptr<CwxContentPanel> m_contentPanel;

    void initUi();
    void initEventListener();
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
};

#endif // LOADER_UI_WX_WX_FRAME_HPP_
