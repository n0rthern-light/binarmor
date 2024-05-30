#pragma once

#include "wx_headers.hpp"
#include <wx/generic/panelg.h>
#include <shared/event/IEventBus.hpp>

class CwxSidebarPanel : public wxPanel
{
    IEventBus* m_eventBus;

public:
    CwxSidebarPanel(wxWindow* parent, IEventBus* t_eventBus);
};

