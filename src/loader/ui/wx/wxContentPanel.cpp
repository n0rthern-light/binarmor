#include "wxContentPanel.hpp"
#include "loader/ui/wx/content/wxBinaryFileInfoPanel.hpp"

CwxContentPanel::CwxContentPanel(wxWindow* parent, IEventBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;
    m_binaryFileInfoPanel = nullptr;

    m_sizer = std::make_unique<wxBoxSizer>(wxVERTICAL);

    m_binaryFileInfoPanel = std::make_unique<CwxBinaryFileInfoPanel>(this, m_eventBus);
    m_sizer->Add(m_binaryFileInfoPanel.get(), 1, wxEXPAND | wxALL, 5);

    this->SetSizer(m_sizer.get());
}

void CwxContentPanel::showFile(const CBinaryFile& binaryFile)
{
    m_binaryFileInfoPanel->showFile(binaryFile);
}

