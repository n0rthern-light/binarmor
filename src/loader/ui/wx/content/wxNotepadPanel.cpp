#include "wxNotepadPanel.hpp"
#include "loader/ui/wx/content/wxBinaryFileInfoPanel.hpp"
#include "loader/ui/wx/wx_headers.hpp"
#include <wx/gdicmn.h>
#include <wx/osx/button.h>
#include <shared/self_obfuscation/strenc.hpp>

CwxNotepadPanel::CwxNotepadPanel(wxWindow* parent, IMessageBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;
    m_sizer = std::make_unique<wxBoxSizer>(wxVERTICAL);

    m_fileName = std::make_unique<wxStaticText>(this, wxID_ANY, strenc(""));
    auto font = m_fileName->GetFont();
    font.SetPointSize(16);
    font.SetWeight(wxFONTWEIGHT_BOLD);
    m_fileName->SetFont(font);
    m_sizer->Add(m_fileName.get(), 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

    m_sizer->AddSpacer(8);

    m_notebook = std::make_unique<wxNotebook>(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1));

    m_binaryFileInfoPanel = std::make_unique<CwxBinaryFileInfoPanel>(m_notebook.get(), m_eventBus);
    m_notebook->AddPage(m_binaryFileInfoPanel.get(), strenc("Binary Info"));

    m_notebook->AddPage(new wxPanel(m_notebook.get(), wxID_ANY), strenc("Anti-Debug"));

    m_notebook->AddPage(new wxPanel(m_notebook.get(), wxID_ANY), strenc("Obfuscation"));

    m_notebook->AddPage(new wxPanel(m_notebook.get(), wxID_ANY), strenc("Virtualization"));

    m_notebook->AddPage(new wxPanel(m_notebook.get(), wxID_ANY), strenc("License Manager"));

    m_sizer->Add(m_notebook.get(), 1, wxEXPAND | wxALL, 0);
    SetSizer(m_sizer.get());
}

void CwxNotepadPanel::loadFileData(const CBinaryFile& binaryFile)
{
    m_fileName->SetLabelText(binaryFile.fileName());
    m_fileName->Update();

    m_binaryFileInfoPanel->loadFileData(binaryFile);
    m_notebook->SetSelection(0);
}

