#include "wxContentPanel.hpp"
#include "loader/ui/wx/content/wxNotepadPanel.hpp"

CwxContentPanel::CwxContentPanel(wxWindow* parent, IMessageBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;

    m_sizer = std::make_unique<wxBoxSizer>(wxVERTICAL);

    m_notepadPanel = std::make_unique<CwxNotepadPanel>(this, m_eventBus);
    m_sizer->Add(m_notepadPanel.get(), 1, wxEXPAND | wxALL, 5);

    m_dragAndDropPanel = std::make_unique<CwxDragAndDropPanel>(this, m_eventBus);
    m_sizer->Add(m_dragAndDropPanel.get(), 1, wxEXPAND | wxALL, 5);

    this->SetSizer(m_sizer.get());

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

