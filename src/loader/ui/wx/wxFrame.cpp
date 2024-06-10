#include "wxFrame.hpp"
#include "../settings.hpp"
#include "wxContentPanel.hpp"
#include "wxSidebarPanel.hpp"
#include "wx_headers.hpp"
#include <memory>
#include <shared/self_obfuscation/strenc.hpp>
#include <core/application/events/NewFileSelectedEvent.hpp>

wxDECLARE_EVENT(EVENT_DISPLAY_WINDOW_OPEN_FILE, wxCommandEvent);
wxDEFINE_EVENT(EVENT_DISPLAY_WINDOW_OPEN_FILE, wxCommandEvent);

CwxFrame::CwxFrame(IMessageBus* t_eventBus): wxFrame(NULL, wxID_ANY, strenc("BinArmor"), wxDefaultPosition, wxSize(WINDOW_SIZE_X, WINDOW_SIZE_Y), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    m_eventBus = t_eventBus;
    m_mainPanel = nullptr;
    m_mainSizer = nullptr;
    m_sidebarPanel = nullptr;
    m_contentPanel = nullptr;

	this->initUi();
	this->initEventListener();
}

void CwxFrame::initUi()
{
    m_mainPanel = std::make_unique<wxPanel>(this, wxID_ANY);
    m_sidebarPanel = std::make_unique<CwxSidebarPanel>(m_mainPanel.get(), m_eventBus);
    m_contentPanel = std::make_unique<CwxContentPanel>(m_mainPanel.get(), m_eventBus);

    m_mainSizer = std::make_unique<wxBoxSizer>(wxHORIZONTAL);
    m_mainSizer->Add(m_sidebarPanel.get(), 0, wxEXPAND | wxALL, 5);
    m_mainSizer->Add(m_contentPanel.get(), 1, wxEXPAND | wxALL, 5);

    m_mainPanel->SetSizer(m_mainSizer.get());

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

void CwxFrame::promptOpenFile()
{
	auto event = new wxCommandEvent(EVENT_DISPLAY_WINDOW_OPEN_FILE); // RIP Smart Pointers
	wxQueueEvent(this, event);
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

