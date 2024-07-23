#include "wxDragAndDropPanel.hpp"
#include "loader/ui/wx/wx_headers.hpp"
#include <shared/self_obfuscation/strenc.hpp>

CwxDragAndDropPanel::CwxDragAndDropPanel(wxWindow* parent, IMessageBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;
    m_sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* centeredText = new wxStaticText(this, wxID_ANY, strenc("Drop a Binary here in order to open it."));
    m_sizer->AddSpacer(225);
    m_sizer->Add(centeredText, 1, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);

    SetBackgroundColour(*wxLIGHT_GREY);

    SetSizerAndFit(m_sizer);
    Layout();
}

