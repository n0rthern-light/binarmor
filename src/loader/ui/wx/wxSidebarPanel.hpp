#pragma once

#include "wx_headers.hpp"
#include <wx/generic/panelg.h>
#include <shared/message/IMessageBus.hpp>
#include <core/file/BinaryFile.hpp>
#include <wx/listctrl.h>

class CwxSidebarPanel : public wxPanel
{
    IMessageBus* m_eventBus;

    std::unique_ptr<wxBoxSizer> m_sizer;

    std::unique_ptr<wxListCtrl> m_fileList;

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
};

