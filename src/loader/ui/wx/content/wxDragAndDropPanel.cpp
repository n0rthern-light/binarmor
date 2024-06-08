#include <core/application/events/NewFileSelectedEvent.hpp>
#include "wxDragAndDropPanel.hpp"
#include "loader/ui/wx/wx_headers.hpp"
#include <shared/self_obfuscation/strenc.hpp>

class FileDropTarget : public wxFileDropTarget {
public:
    FileDropTarget(CwxDragAndDropPanel* panel) : m_panel(panel) {}

    virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames) override {
        auto dragAndDropPanel = dynamic_cast<CwxDragAndDropPanel*>(m_panel);
        dragAndDropPanel->notifyAboutNewFile(std::string(filenames[0]));
        return true;
    }

private:
    wxPanel* m_panel;
};

CwxDragAndDropPanel::CwxDragAndDropPanel(wxWindow* parent, IMessageBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;
    m_sizer = std::make_unique<wxBoxSizer>(wxVERTICAL);

    wxStaticText* centeredText = new wxStaticText(this, wxID_ANY, strenc("Drop a Binary here in order to open it."));
    m_sizer->AddSpacer(225);
    m_sizer->Add(centeredText, 1, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);

    SetBackgroundColour(*wxLIGHT_GREY);
    FileDropTarget* dropTarget = new FileDropTarget(this);
    SetDropTarget(dropTarget);

    SetSizerAndFit(m_sizer.get());
    Layout();
}

void CwxDragAndDropPanel::notifyAboutNewFile(const std::string& path)
{
    m_eventBus->publish(std::make_shared<CNewFileSelectedEvent>(path.c_str()));
}

