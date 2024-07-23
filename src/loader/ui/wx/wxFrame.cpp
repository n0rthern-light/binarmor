#include "wxFrame.hpp"
#include "../settings.hpp"
#include "components/FileDropTarget.hpp"
#include "wxContentPanel.hpp"
#include "wxSidebarPanel.hpp"
#include <memory>
#include <shared/self_obfuscation/strenc.hpp>
#include <core/application/events/NewFileSelectedEvent.hpp>
#include <wx/event.h>

wxDECLARE_EVENT(EVENT_DISPLAY_WINDOW_OPEN_FILE, wxCommandEvent);
wxDEFINE_EVENT(EVENT_DISPLAY_WINDOW_OPEN_FILE, wxCommandEvent);

CwxFrame::CwxFrame(IMessageBus* t_eventBus): wxFrame(NULL, wxID_ANY, strenc("BinArmor"), wxDefaultPosition, wxSize(WINDOW_SIZE_X, WINDOW_SIZE_Y), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    m_eventBus = t_eventBus;
    m_mainPanel = nullptr;
    m_mainSizer = nullptr;
    m_sidebarPanel = nullptr;
    m_contentPanel = nullptr;

    initUi();
    initEventListener();
    initFileDrop();
}

void CwxFrame::initUi()
{
    m_mainPanel = new wxPanel(this, wxID_ANY);
    m_sidebarPanel = new CwxSidebarPanel(m_mainPanel, m_eventBus);
    m_contentPanel = new CwxContentPanel(m_mainPanel, m_eventBus);

    m_mainSizer = new wxBoxSizer(wxHORIZONTAL);
    m_mainSizer->Add(m_sidebarPanel, 0, wxEXPAND | wxALL, 5);
    m_mainSizer->Add(m_contentPanel, 1, wxEXPAND | wxALL, 5);

    m_mainPanel->SetSizer(m_mainSizer);

    CreateStatusBar();
    SetStatusText(strenc("Welcome to BinArmor v0.1"));
}

void CwxFrame::initEventListener()
{
    Bind(EVENT_DISPLAY_WINDOW_OPEN_FILE, &CwxFrame::onEventDisplayWindowOpenFile, this);
}

void CwxFrame::onEventDisplayWindowOpenFile(wxCommandEvent& wxCommandEvent)
{
    wxFileDialog fileDialog(this, strenc("Open Text File"), strenc(""), strenc(""),
        strenc("Portable Executables (*.exe;*.dll)|*.exe;*.dll|All files (*.*)|*.*"),
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (fileDialog.ShowModal() == wxID_CANCEL) {
        return; 
    }

    wxString filePath = fileDialog.GetPath();
    m_eventBus->publish(std::make_shared<CNewFileSelectedEvent>(filePath.c_str()));
}

void CwxFrame::initFileDrop()
{
    auto dropTarget = new CFileDropTarget([&](vec_file_paths files) {
        for(const auto& file : files) {
            notifyAboutNewFile(file.string());
        }
    });
    SetDropTarget(dropTarget);
}

void CwxFrame::promptOpenFile()
{
    auto event = new wxCommandEvent(EVENT_DISPLAY_WINDOW_OPEN_FILE); // RIP Smart Pointers
    wxQueueEvent(this, event);
}

void CwxFrame::highlightBinaryFileInList(const file_id& fileId)
{
    m_sidebarPanel->highlightFile(fileId);
}

void CwxFrame::removeFromFileList(const file_id& fileId)
{
    m_sidebarPanel->removeFromLoadedFiles(fileId);
}

void CwxFrame::displayBinaryFile(const CBinaryFile& binaryFile)
{
    m_contentPanel->showFile(binaryFile);
}

void CwxFrame::appendToLoadedFiles(const CBinaryFile* binary)
{
    m_sidebarPanel->appendToLoadedFiles(binary);
}

void CwxFrame::displayEmpty()
{
    m_contentPanel->showDragAndDrop();
}

void CwxFrame::displayStatus(const std::string& statusText)
{
    SetStatusText(statusText);
}

void CwxFrame::notifyAboutNewFile(const std::string& path)
{
    m_eventBus->publish(std::make_shared<CNewFileSelectedEvent>(path.c_str()));
}

