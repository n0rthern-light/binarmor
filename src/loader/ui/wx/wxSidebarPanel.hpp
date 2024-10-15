#ifndef LOADER_UI_WX_WX_SIDEBAR_PANEL_HPP_
#define LOADER_UI_WX_WX_SIDEBAR_PANEL_HPP_

#include "wx_headers.hpp"
#include <shared/message/IMessageBus.hpp>
#include <core/file/BinaryFile.hpp>
#include <wx/listbase.h>
#include <map>

class CwxSidebarPanel : public wxPanel
{
    IMessageBus* m_eventBus;

    wxBoxSizer* m_sizer;

    wxListCtrl* m_fileList;
    std::vector<program::core::file::file_id> m_fileListIds;
    long m_fileListSelected;

    wxButton* m_btnOpenFile;
    wxButton* m_btnUnloadFile;
    wxButton* m_btnAntiDebugging;
    wxButton* m_btnObfuscation;
    wxButton* m_btnVirtualization;
    wxButton* m_btnLicenseManager;
    wxButton* m_btnExportFile;
    wxButton* m_btnHelp;
    
    void toggleFileManagementButtons();
    void update();
public:
    CwxSidebarPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void appendToLoadedFiles(const program::core::file::CBinaryFile* binary);
    void removeFromLoadedFiles(const program::core::file::file_id& itemId);
    void highlightFile(const program::core::file::file_id& fileId);
    void onFileSelected(const wxListEvent& wxEvent);
    void onFileDoubleClicked(const wxListEvent& wxEvent);
    void onUnloadBtn(const wxEvent& wxEvent);
};

#endif // LOADER_UI_WX_WX_SIDEBAR_PANEL_HPP_
