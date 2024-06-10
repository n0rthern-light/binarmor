#include "wxSidebarPanel.hpp"
#include "bitmap.hpp"
#include "../icons.hpp"
#include "../../application/events/UIRequestedOpenFileEvent.hpp"
#include <core/application/events/WorkFileChangeRequestedEvent.hpp>
#include <core/application/events/FileUnloadRequestedEvent.hpp>
#include <core/file/BinaryFile.hpp>
#include <shared/self_obfuscation/strenc.hpp>
#include <memory>
#include <wx/listbase.h>

CwxSidebarPanel::CwxSidebarPanel(wxWindow* parent, IMessageBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;

    this->SetMinSize(wxSize(180, 400));
    m_sizer = std::make_unique<wxBoxSizer>(wxVERTICAL);
    this->SetSizer(m_sizer.get());

    m_btnOpenFile = std::make_unique<wxButton>(this, wxID_ANY, strenc("Open File"));
    m_btnOpenFile->SetBitmap(Bitmap::CreateFromBuffer(iconOpenFile));
    m_btnOpenFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
        m_eventBus->publish(std::make_shared<CUIRequestedOpenFileEvent>());
    });

    m_fileList = std::make_unique<wxListCtrl>(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
    m_fileList->AppendColumn(strenc("Loaded Files"), wxLIST_FORMAT_LEFT, 170);
    m_fileList->Bind(wxEVT_LIST_ITEM_SELECTED, &CwxSidebarPanel::onFileSelected, this);
    m_fileList->Bind(wxEVT_LIST_ITEM_ACTIVATED, &CwxSidebarPanel::onFileDoubleClicked, this);
    m_fileListIds = { };
    m_fileListSelected = -1;

    m_btnUnloadFile = std::make_unique<wxButton>(this, wxID_ANY, strenc("Unload File"));
    m_btnUnloadFile->Bind(wxEVT_BUTTON, &CwxSidebarPanel::onUnloadBtn, this); 

    m_btnExportFile = std::make_unique<wxButton>(this, wxID_ANY, strenc("Export File"));
    m_btnExportFile->SetBitmap(Bitmap::CreateFromBuffer(iconExport));
    m_btnExportFile->Disable();

    m_btnHelp = std::make_unique<wxButton>(this, wxID_ANY, strenc("Help"));

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
    m_fileListIds[index] = binary->fileId();
}

void CwxSidebarPanel::highlightFile(const file_id& fileId)
{
    for(const auto& pair : m_fileListIds) {
        if (pair.second == fileId) {
            m_fileList->SetItemState(pair.first, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
            m_fileList->EnsureVisible(pair.first);
            m_fileListSelected = pair.first;
        } else {
            m_fileList->SetItemState(pair.first, 0, wxLIST_STATE_SELECTED);
        }
    }
}

void CwxSidebarPanel::removeFromLoadedFiles(const file_id& fileId)
{
   for (auto it = m_fileListIds.begin(); it != m_fileListIds.end(); ) {
        if (it->second == fileId) {
            m_fileList->DeleteItem(it->first);
            it = m_fileListIds.erase(it);
        } else {
            ++it;
        }
    }

    m_fileListSelected = -1;
}

void CwxSidebarPanel::onFileSelected(const wxListEvent& wxEvent)
{
    auto index = wxEvent.GetIndex();

    m_fileListSelected = index;
}

void CwxSidebarPanel::onFileDoubleClicked(const wxListEvent& wxEvent)
{
    int index = wxEvent.GetIndex();

    m_eventBus->publish(std::make_shared<CWorkFileChangeRequestedEvent>(m_fileListIds.at(index)));
}

void CwxSidebarPanel::onUnloadBtn(const wxEvent& event)
{
    if (m_fileListSelected == -1) {
        throw RuntimeException(strenc("Select a file first."));
    }

    m_eventBus->publish(std::make_shared<CFileUnloadRequestedEvent>(m_fileListIds.at(m_fileListSelected)));
}

