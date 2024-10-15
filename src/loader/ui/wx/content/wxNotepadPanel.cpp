#include "wxNotepadPanel.hpp"
#include "loader/ui/wx/content/wxBinaryFileInfoPanel.hpp"
#include "loader/ui/wx/wx_headers.hpp"
#include <shared/self_obfuscation/strenc.hpp>

using namespace program::core::file;

CwxNotepadPanel::CwxNotepadPanel(wxWindow* parent, IMessageBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;
    m_sizer = new wxBoxSizer(wxVERTICAL);

    m_fileName = new wxStaticText(this, wxID_ANY, strenc(""));
    auto font = m_fileName->GetFont();
    font.SetPointSize(16);
    font.SetWeight(wxFONTWEIGHT_BOLD);
    m_fileName->SetFont(font);
    m_sizer->Add(m_fileName, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

    m_sizer->AddSpacer(8);

    m_notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1));

    m_binaryFileInfoPanel = new CwxBinaryFileInfoPanel(m_notebook, m_eventBus);
    m_notebook->AddPage(m_binaryFileInfoPanel, strenc("Binary Info"));

    m_notebook->AddPage(new wxPanel(m_notebook, wxID_ANY), strenc("Anti-Debug"));

    m_notebook->AddPage(new wxPanel(m_notebook, wxID_ANY), strenc("Obfuscation"));

    m_notebook->AddPage(new wxPanel(m_notebook, wxID_ANY), strenc("Virtualization"));

    m_notebook->AddPage(new wxPanel(m_notebook, wxID_ANY), strenc("License Manager"));

    m_sizer->Add(m_notebook, 1, wxEXPAND | wxALL, 0);
    SetSizer(m_sizer);
}

void CwxNotepadPanel::loadFileData(const CBinaryFile& binaryFile)
{
    m_fileName->SetLabelText(binaryFile.fileName());
    m_fileName->Update();

    m_binaryFileInfoPanel->loadFileData(binaryFile);
    m_notebook->SetSelection(0);
}

