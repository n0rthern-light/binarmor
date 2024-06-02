#include <core/application/events/NewFileSelectedEvent.hpp>
#include "loader/ui/wx/content/wxDrangAndDropPanel.hpp"
#include "loader/ui/wx/wx_headers.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <wx/dnd.h>
#include <wx/sizer.h>

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
    m_sizer = std::make_shared<wxBoxSizer>(wxVERTICAL);

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
    //wxMessageBox(path, "File Dropped");
    m_eventBus->publish(new CNewFileSelectedEvent(path.c_str()));
}

