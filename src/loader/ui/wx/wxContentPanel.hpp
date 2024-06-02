#pragma once

#include "loader/ui/wx/content/wxDrangAndDropPanel.hpp"
#include "loader/ui/wx/content/wxNotepadPanel.hpp"
#include "wx_headers.hpp"
#include <wx/generic/panelg.h>
#include <shared/message/IMessageBus.hpp>
#include <wx/sizer.h>

class CwxContentPanel : public wxPanel
{
    IMessageBus* m_eventBus;
    std::shared_ptr<wxBoxSizer> m_sizer;
    std::shared_ptr<CwxNotepadPanel> m_notepadPanel;
    std::shared_ptr<CwxDragAndDropPanel> m_dragAndDropPanel;

public:
    CwxContentPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void hideAll();
    void showFile(const CBinaryFile& binaryFile);
    void showDragAndDrop();
};

