#ifndef LOADER_UI_WX_WX_CONTENT_PANEL_HPP_
#define LOADER_UI_WX_WX_CONTENT_PANEL_HPP_

#include "wx_headers.hpp"
#include "loader/ui/wx/content/wxDragAndDropPanel.hpp"
#include "loader/ui/wx/content/wxNotepadPanel.hpp"
#include <shared/message/IMessageBus.hpp>

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

#endif // LOADER_UI_WX_WX_CONTENT_PANEL_HPP_
