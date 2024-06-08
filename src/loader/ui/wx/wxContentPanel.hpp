#pragma once

#include "loader/ui/wx/content/wxDragAndDropPanel.hpp"
#include "loader/ui/wx/content/wxNotepadPanel.hpp"
#include "wx_headers.hpp"
#include <wx/generic/panelg.h>
#include <shared/message/IMessageBus.hpp>
#include <wx/sizer.h>

class CwxContentPanel : public wxPanel
{
    IMessageBus* m_eventBus;
    std::unique_ptr<wxBoxSizer> m_sizer;
    std::unique_ptr<CwxNotepadPanel> m_notepadPanel;
    std::unique_ptr<CwxDragAndDropPanel> m_dragAndDropPanel;

public:
    CwxContentPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void hideAll();
    void showFile(const CBinaryFile& binaryFile);
    void showDragAndDrop();
};

