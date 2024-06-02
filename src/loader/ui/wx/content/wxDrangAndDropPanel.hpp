#pragma once

#include "../wx_headers.hpp"
#include "core/file/BinaryFile.hpp"
#include <wx/generic/panelg.h>
#include <shared/message/IMessageBus.hpp>
#include <wx/sizer.h>
#include <map>

class CwxDragAndDropPanel : public wxPanel
{
    IMessageBus* m_eventBus;
    std::shared_ptr<wxSizer> m_sizer;
public:
    CwxDragAndDropPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void notifyAboutNewFile(const std::string& path);
};

