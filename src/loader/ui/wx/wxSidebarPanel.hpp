#pragma once

#include "wx_headers.hpp"
#include <wx/generic/panelg.h>
#include <shared/message/IMessageBus.hpp>

class CwxSidebarPanel : public wxPanel
{
    IMessageBus* m_eventBus;

    std::unique_ptr<wxBoxSizer> m_sizer;

    std::shared_ptr<wxButton> m_btnOpenFile;
    std::shared_ptr<wxButton> m_btnExportFile;
    std::shared_ptr<wxButton> m_btnAntiDebugging;
    std::shared_ptr<wxButton> m_btnObfuscation;
    std::shared_ptr<wxButton> m_btnVirtualization;
    std::shared_ptr<wxButton> m_btnLicenseManager;
    std::shared_ptr<wxButton> m_btnHelp;

    std::vector<std::shared_ptr<wxButton>> featureButtons();
public:
    CwxSidebarPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void lockFeatureButtons();
    void unlockFeatureButtons();
};

