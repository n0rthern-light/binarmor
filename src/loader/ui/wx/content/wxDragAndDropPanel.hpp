#ifndef LOADER_UI_WX_CONTENT_WX_DRAG_AND_DROP_PANEL_HPP_
#define LOADER_UI_WX_CONTENT_WX_DRAG_AND_DROP_PANEL_HPP_

#include "../wx_headers.hpp"
#include "core/file/BinaryFile.hpp"
#include <shared/message/IMessageBus.hpp>
#include <map>

class CwxDragAndDropPanel : public wxPanel
{
    IMessageBus* m_eventBus;
    std::unique_ptr<wxSizer> m_sizer;
public:
    CwxDragAndDropPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void notifyAboutNewFile(const std::string& path);
};

#endif // LOADER_UI_WX_CONTENT_WX_DRAG_AND_DROP_PANEL_HPP_
