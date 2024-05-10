#include "wxFrame.hpp"
#include "bitmap.hpp"
#include "../icons.hpp"
#include "../settings.hpp"
#include "../../container.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <core/file/UIRequestedOpenFile.hpp>
#include <core/file/NewFileSelected.hpp>

void CwxFrame::initUi()
{
    // Main panel
    wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
    mainPanel->SetBackgroundColour(*wxWHITE);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    // Main content area
    wxPanel* contentPanel = new wxPanel(mainPanel, wxID_ANY);
    contentPanel->SetBackgroundColour(*wxWHITE);
    contentPanel->SetMinSize(wxSize(300, 400));
    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);
    contentPanel->SetSizer(contentSizer);

    wxTextCtrl* textCtrl = new wxTextCtrl(
        contentPanel,
        wxID_ANY,
        strenc("This is read-only text displayed using wxTextCtrl."),
        wxPoint(0, 0),
        wxSize(0, 0),
        wxTE_READONLY | wxTE_MULTILINE
    );
    contentSizer->Add(textCtrl, 1, wxEXPAND | wxALL, 5);

    // Sidebar area (fixed width)
    wxPanel* sidebarPanel = new wxPanel(mainPanel, wxID_ANY);
    sidebarPanel->SetBackgroundColour(*wxWHITE);
    sidebarPanel->SetMinSize(wxSize(180, 400)); // Fixed sidebar size

    // Sidebar layout
    wxBoxSizer* sidebarSizer = new wxBoxSizer(wxVERTICAL);
    sidebarPanel->SetSizer(sidebarSizer);

    auto btnOpenFile = new wxButton(sidebarPanel, wxID_ANY, strenc("Open File"));
    btnOpenFile->SetBitmap(Bitmap::CreateFromBuffer(iconOpenFile));
    btnOpenFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
        this->eventBus->publish(new CUIRequestedOpenFile());
    });
    auto btnExportFile = new wxButton(sidebarPanel, wxID_ANY, strenc("Export File"));
    btnExportFile->SetBitmap(Bitmap::CreateFromBuffer(iconExport));
    btnExportFile->Disable();
    auto btnAntiDebugging = new wxButton(sidebarPanel, wxID_ANY, strenc("Anti-Debug"));
    btnAntiDebugging->SetBitmap(Bitmap::CreateFromBuffer(iconNoPreview));
    btnAntiDebugging->Disable();
    auto btnObfuscation = new wxButton(sidebarPanel, wxID_ANY, strenc("Obfuscation"));
    btnObfuscation->SetBitmap(Bitmap::CreateFromBuffer(iconObfuscation));
    btnObfuscation->Disable();
    auto btnVirtualization = new wxButton(sidebarPanel, wxID_ANY, strenc("Virtualization"));
    btnVirtualization->SetBitmap(Bitmap::CreateFromBuffer(iconVirtualization));
    btnVirtualization->Disable();
    auto btnLicenseManager = new wxButton(sidebarPanel, wxID_ANY, strenc("Licensing"));
    btnLicenseManager->SetBitmap(Bitmap::CreateFromBuffer(iconLicensing));
    btnLicenseManager->Disable();
    auto btnHelp = new wxButton(sidebarPanel, wxID_ANY, strenc("Help"));

    // Add buttons to the sidebar sizer

    sidebarSizer->Add(btnOpenFile, 0, wxEXPAND | wxALL, 5);
    sidebarSizer->AddSpacer(15);
    sidebarSizer->Add(btnAntiDebugging, 0, wxEXPAND | wxALL, 5);
    sidebarSizer->Add(btnObfuscation, 0, wxEXPAND | wxALL, 5);
    sidebarSizer->Add(btnVirtualization, 0, wxEXPAND | wxALL, 5);
    sidebarSizer->Add(btnLicenseManager, 0, wxEXPAND | wxALL, 5);
    sidebarSizer->AddStretchSpacer(1);
    sidebarSizer->Add(btnExportFile, 0, wxEXPAND | wxALL, 5);
    sidebarSizer->Add(btnHelp, 0, wxEXPAND | wxALL, 5);

    // Add panels to sizericonVir
    mainSizer->Add(sidebarPanel, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(contentPanel, 1, wxEXPAND | wxALL, 5);

    mainPanel->SetSizer(mainSizer);

    CreateStatusBar();
    SetStatusText(strenc("Welcome to BinArmor v0.1"));
}

CwxFrame::CwxFrame(IEventBus* _eventBus): wxFrame(NULL, wxID_ANY, strenc("BinArmor"), wxDefaultPosition, wxSize(WINDOW_SIZE_X, WINDOW_SIZE_Y), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    eventBus = _eventBus;

    this->initUi();
}

void CwxFrame::promptOpenFile()
{
    wxFileDialog openFileDialog(this, strenc("Open Text File"), strenc(""), strenc(""),
        strenc("Portable Executables (*.exe;*.dll)|*.exe;*.dll|All files (*.*)|*.*"),
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return; 
    }

    wxString filePath = openFileDialog.GetPath();
    eventBus->publish(new CNewFileSelected(filePath.c_str()));
}
