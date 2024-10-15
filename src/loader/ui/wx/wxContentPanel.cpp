#include "wxContentPanel.hpp"
#include "loader/ui/wx/content/wxNotepadPanel.hpp"

using namespace program::core::file;

CwxContentPanel::CwxContentPanel(wxWindow* parent, IMessageBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;

    m_sizer = new wxBoxSizer(wxVERTICAL);

    m_notepadPanel = new CwxNotepadPanel(this, m_eventBus);
    m_sizer->Add(m_notepadPanel, 1, wxEXPAND | wxALL, 5);

    m_dragAndDropPanel = new CwxDragAndDropPanel(this, m_eventBus);
    m_sizer->Add(m_dragAndDropPanel, 1, wxEXPAND | wxALL, 5);

    this->SetSizer(m_sizer);

    showDragAndDrop();
}

void CwxContentPanel::hideAll()
{
    m_notepadPanel->Hide();
    m_dragAndDropPanel->Hide();
}

void CwxContentPanel::showFile(const CBinaryFile& binaryFile)
{
    hideAll();
    m_notepadPanel->loadFileData(binaryFile);
    m_notepadPanel->Show();
    m_sizer->Layout();
}

void CwxContentPanel::showDragAndDrop()
{
    hideAll();
    m_dragAndDropPanel->Show();
    m_sizer->Layout();
}

