#include "wxContentPanel.hpp"
#include "loader/ui/wx/content/wxBinaryFileInfoPanel.hpp"

CwxContentPanel::CwxContentPanel(wxWindow* parent, IMessageBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;
    m_binaryFileInfoPanel = nullptr;

    m_sizer = std::make_shared<wxBoxSizer>(wxVERTICAL);

    m_binaryFileInfoPanel = std::make_shared<CwxBinaryFileInfoPanel>(this, m_eventBus);
    m_sizer->Add(m_binaryFileInfoPanel.get(), 1, wxEXPAND | wxALL, 5);

    this->SetSizer(m_sizer.get());

    hideAll();
}

void CwxContentPanel::hideAll()
{
    m_binaryFileInfoPanel->Hide();
}

void CwxContentPanel::showFile(const CBinaryFile& binaryFile)
{
    m_binaryFileInfoPanel->loadFileData(binaryFile);
    m_binaryFileInfoPanel->Show();
    m_sizer->Layout();
}

void CwxContentPanel::showDragAndDrop()
{

}

