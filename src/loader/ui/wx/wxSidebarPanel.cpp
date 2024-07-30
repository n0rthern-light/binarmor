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
    m_sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_sizer);

    m_btnOpenFile = new wxButton(this, wxID_ANY, strenc("Open File"));
    m_btnOpenFile->SetBitmap(Bitmap::CreateFromBuffer(iconOpenFile));
    m_btnOpenFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
        m_eventBus->publish(std::make_shared<CUIRequestedOpenFileEvent>());
    });

    m_fileList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
    m_fileList->AppendColumn(strenc("Loaded Files"), wxLIST_FORMAT_LEFT, 170);
    m_fileList->Bind(wxEVT_LIST_ITEM_SELECTED, &CwxSidebarPanel::onFileSelected, this);
    m_fileList->Bind(wxEVT_LIST_ITEM_ACTIVATED, &CwxSidebarPanel::onFileDoubleClicked, this);
    m_fileListIds = { };
    m_fileListSelected = -1;

    m_btnUnloadFile = new wxButton(this, wxID_ANY, strenc("Unload File"));
    m_btnUnloadFile->Bind(wxEVT_BUTTON, &CwxSidebarPanel::onUnloadBtn, this); 

    m_btnExportFile = new wxButton(this, wxID_ANY, strenc("Export File"));
    m_btnExportFile->SetBitmap(Bitmap::CreateFromBuffer(iconExport));
    m_btnExportFile->Disable();

    m_btnHelp = new wxButton(this, wxID_ANY, strenc("Help"));

    m_sizer->Add(m_btnOpenFile, 0, wxEXPAND | wxALL, 5);
    m_sizer->Add(m_fileList, 0, wxEXPAND | wxALL, 5);
    m_sizer->Add(m_btnUnloadFile, 0, wxEXPAND | wxALL, 5);
    m_sizer->AddStretchSpacer(1);
    m_sizer->Add(m_btnExportFile, 0, wxEXPAND | wxALL, 5);
    m_sizer->Add(m_btnHelp, 0, wxEXPAND | wxALL, 5);

    update();
} 

void CwxSidebarPanel::appendToLoadedFiles(const CBinaryFile* binary)
{
    auto index = m_fileList->GetItemCount();
    m_fileList->InsertItem(index, binary->fileName().c_str());
    m_fileList->CheckItem(index, true);
    m_fileListIds.push_back(binary->fileId());

    update();
}

void CwxSidebarPanel::removeFromLoadedFiles(const file_id& fileId)
{
    auto i = 0;
    for (auto it = m_fileListIds.begin(); it != m_fileListIds.end(); ) {
        if (strcmp(it->c_str(), fileId.c_str()) == 0) {
            m_fileList->DeleteItem(i);
            it = m_fileListIds.erase(it);
        } else {
            ++it;
            ++i;
        }
    }

    m_fileListSelected = -1;

    update();
}

void CwxSidebarPanel::highlightFile(const file_id& fileId)
{
    for(auto i = 0; i < m_fileListIds.size(); ++i) {
        const auto cur = m_fileListIds[i];
        if (cur == fileId) {
            m_fileList->SetItemState(i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
            m_fileList->EnsureVisible(i);
            m_fileListSelected = i;
        } else {
            m_fileList->SetItemState(i, 0, wxLIST_STATE_SELECTED);
        }
    }
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

void CwxSidebarPanel::toggleFileManagementButtons()
{
    const auto& itemCount = m_fileListIds.size();

    if (itemCount == 1) {
        m_btnUnloadFile->Enable();
    } else if (itemCount == 0) {
        m_btnUnloadFile->Disable();
    }
}

void CwxSidebarPanel::update()
{
    toggleFileManagementButtons();
}

