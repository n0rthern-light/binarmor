#include "wxSidebarPanel.hpp"
#include "bitmap.hpp"
#include "../icons.hpp"
#include <core/file/events/UIRequestedOpenFileEvent.hpp>

CwxSidebarPanel::CwxSidebarPanel(wxWindow* parent, IEventBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;

    this->SetMinSize(wxSize(180, 400)); // Fixed sidebar size
    wxBoxSizer* sidebarSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sidebarSizer);

    auto btnOpenFile = new wxButton(this, wxID_ANY, strenc("Open File"));
    btnOpenFile->SetBitmap(Bitmap::CreateFromBuffer(iconOpenFile));
    btnOpenFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
        m_eventBus->publish(new CUIRequestedOpenFileEvent());
    });
    auto btnExportFile = new wxButton(this, wxID_ANY, strenc("Export File"));
    btnExportFile->SetBitmap(Bitmap::CreateFromBuffer(iconExport));
    btnExportFile->Disable();
    auto btnAntiDebugging = new wxButton(this, wxID_ANY, strenc("Anti-Debug"));
    btnAntiDebugging->SetBitmap(Bitmap::CreateFromBuffer(iconNoPreview));
    btnAntiDebugging->Disable();
    auto btnObfuscation = new wxButton(this, wxID_ANY, strenc("Obfuscation"));
    btnObfuscation->SetBitmap(Bitmap::CreateFromBuffer(iconObfuscation));
    btnObfuscation->Disable();
    auto btnVirtualization = new wxButton(this, wxID_ANY, strenc("Virtualization"));
    btnVirtualization->SetBitmap(Bitmap::CreateFromBuffer(iconVirtualization));
    btnVirtualization->Disable();
    auto btnLicenseManager = new wxButton(this, wxID_ANY, strenc("Licensing"));
    btnLicenseManager->SetBitmap(Bitmap::CreateFromBuffer(iconLicensing));
    btnLicenseManager->Disable();
    auto btnHelp = new wxButton(this, wxID_ANY, strenc("Help"));

    sidebarSizer->Add(btnOpenFile, 0, wxEXPAND | wxALL, 5);
    sidebarSizer->AddSpacer(15);
    sidebarSizer->Add(btnAntiDebugging, 0, wxEXPAND | wxALL, 5);
    sidebarSizer->Add(btnObfuscation, 0, wxEXPAND | wxALL, 5);
    sidebarSizer->Add(btnVirtualization, 0, wxEXPAND | wxALL, 5);
    sidebarSizer->Add(btnLicenseManager, 0, wxEXPAND | wxALL, 5);
    sidebarSizer->AddStretchSpacer(1);
    sidebarSizer->Add(btnExportFile, 0, wxEXPAND | wxALL, 5);
    sidebarSizer->Add(btnHelp, 0, wxEXPAND | wxALL, 5);
} 

