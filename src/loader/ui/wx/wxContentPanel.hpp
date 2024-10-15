#ifndef LOADER_UI_WX_WX_CONTENT_PANEL_HPP_
#define LOADER_UI_WX_WX_CONTENT_PANEL_HPP_

#include "wx_headers.hpp"
#include "loader/ui/wx/content/wxDragAndDropPanel.hpp"
#include "loader/ui/wx/content/wxNotepadPanel.hpp"
#include <shared/message/IMessageBus.hpp>

class CwxContentPanel : public wxPanel
{
    IMessageBus* m_eventBus;
    wxBoxSizer* m_sizer;
    CwxNotepadPanel* m_notepadPanel;
    CwxDragAndDropPanel* m_dragAndDropPanel;

public:
    CwxContentPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void hideAll();
    void showFile(const program::core::file::CBinaryFile& binaryFile);
    void showDragAndDrop();
};

#endif // LOADER_UI_WX_WX_CONTENT_PANEL_HPP_
