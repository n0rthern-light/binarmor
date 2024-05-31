#pragma once

#include "wx_headers.hpp"
#include <wx/generic/panelg.h>
#include <shared/message/IMessageBus.hpp>

class CwxSidebarPanel : public wxPanel
{
    IMessageBus* m_eventBus;

public:
    CwxSidebarPanel(wxWindow* parent, IMessageBus* t_eventBus);
};

