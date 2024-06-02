#pragma once

#include "loader/ui/wx/content/wxBinaryFileInfoPanel.hpp"
#include "wx_headers.hpp"
#include <wx/generic/panelg.h>
#include <shared/message/IMessageBus.hpp>
#include <wx/sizer.h>

class CwxContentPanel : public wxPanel
{
    IMessageBus* m_eventBus;
    std::shared_ptr<wxBoxSizer> m_sizer;
    std::shared_ptr<CwxBinaryFileInfoPanel> m_binaryFileInfoPanel;

public:
    CwxContentPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void hideAll();
    void showFile(const CBinaryFile& binaryFile);
    void showDragAndDrop();
};

