#pragma once

#include "loader/ui/wx/content/wxBinaryFileInfoPanel.hpp"
#include "wx_headers.hpp"
#include <wx/generic/panelg.h>
#include <shared/event/IEventBus.hpp>
#include <wx/sizer.h>

class CwxContentPanel : public wxPanel
{
    IEventBus* m_eventBus;
    std::unique_ptr<wxBoxSizer> m_sizer;
    std::unique_ptr<CwxBinaryFileInfoPanel> m_binaryFileInfoPanel;

public:
    CwxContentPanel(wxWindow* parent, IEventBus* t_eventBus);
    void showFile(const CBinaryFile& binaryFile);
};

