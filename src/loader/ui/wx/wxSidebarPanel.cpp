#include "wxSidebarPanel.hpp"
#include "bitmap.hpp"
#include "../icons.hpp"
#include "../../application/events/UIRequestedOpenFileEvent.hpp"
#include "core/file/BinaryFile.hpp"
#include "loader/ui/wx/wx_headers.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <memory>
#include <wx/gdicmn.h>
#include <wx/listbase.h>

CwxSidebarPanel::CwxSidebarPanel(wxWindow* parent, IMessageBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;

    this->SetMinSize(wxSize(180, 400));
    m_sizer = std::make_unique<wxBoxSizer>(wxVERTICAL);
    this->SetSizer(m_sizer.get());

    m_btnOpenFile = std::make_shared<wxButton>(this, wxID_ANY, strenc("Open File"));
    m_btnOpenFile->SetBitmap(Bitmap::CreateFromBuffer(iconOpenFile));
    m_btnOpenFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
        m_eventBus->publish(std::make_shared<CUIRequestedOpenFileEvent>());
    });

    m_fileList = std::make_shared<wxListCtrl>(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
    m_fileList->AppendColumn(strenc("Loaded Files"), wxLIST_FORMAT_LEFT, 170);

    m_btnUnloadFile = std::make_shared<wxButton>(this, wxID_ANY, strenc("Unload File"));

    m_btnExportFile = std::make_shared<wxButton>(this, wxID_ANY, strenc("Export File"));
    m_btnExportFile->SetBitmap(Bitmap::CreateFromBuffer(iconExport));
    m_btnExportFile->Disable();

    m_btnHelp = std::make_shared<wxButton>(this, wxID_ANY, strenc("Help"));

    m_sizer->Add(m_btnOpenFile.get(), 0, wxEXPAND | wxALL, 5);
    m_sizer->Add(m_fileList.get(), 0, wxEXPAND | wxALL, 5);
    m_sizer->Add(m_btnUnloadFile.get(), 0, wxEXPAND | wxALL, 5);
    m_sizer->AddStretchSpacer(1);
    m_sizer->Add(m_btnExportFile.get(), 0, wxEXPAND | wxALL, 5);
    m_sizer->Add(m_btnHelp.get(), 0, wxEXPAND | wxALL, 5);
} 

void CwxSidebarPanel::appendToLoadedFiles(const CBinaryFile* binary)
{
    auto index = m_fileList->GetItemCount();
    m_fileList->InsertItem(index, binary->fileName().c_str());
    m_fileList->CheckItem(index, true);
}

