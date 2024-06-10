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

    std::unique_ptr<wxBoxSizer> m_sizer;

    std::unique_ptr<wxListCtrl> m_fileList;
    std::map<long, file_id> m_fileListIds;
    long m_fileListSelected;

    std::unique_ptr<wxButton> m_btnOpenFile;
    std::unique_ptr<wxButton> m_btnUnloadFile;
    std::unique_ptr<wxButton> m_btnAntiDebugging;
    std::unique_ptr<wxButton> m_btnObfuscation;
    std::unique_ptr<wxButton> m_btnVirtualization;
    std::unique_ptr<wxButton> m_btnLicenseManager;
    std::unique_ptr<wxButton> m_btnExportFile;
    std::unique_ptr<wxButton> m_btnHelp;

public:
    CwxSidebarPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void appendToLoadedFiles(const CBinaryFile* binary);
    void highlightFile(const file_id& fileId);
    void removeFromLoadedFiles(const file_id& itemId);
    void onFileSelected(const wxListEvent& wxEvent);
    void onFileDoubleClicked(const wxListEvent& wxEvent);
    void onUnloadBtn(const wxEvent& wxEvent);
};

#endif // LOADER_UI_WX_WX_SIDEBAR_PANEL_HPP_
