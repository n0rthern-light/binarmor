#include <iostream>
#include <iostream>
#include "settings.hpp"
#include "icons.hpp"
#include "bitmap.hpp"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler());

    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(): wxFrame(NULL, wxID_ANY, "BinArmor", wxDefaultPosition, wxSize(WINDOW_SIZE_X, WINDOW_SIZE_Y), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
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
        "This is read-only text displayed using wxTextCtrl.",
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

    auto btnOpenFile = new wxButton(sidebarPanel, wxID_ANY, "Open File");
    btnOpenFile->SetBitmap(Bitmap::CreateFromBuffer(iconOpenFile));
    auto btnExportFile = new wxButton(sidebarPanel, wxID_ANY, "Export File");
    btnExportFile->SetBitmap(Bitmap::CreateFromBuffer(iconExport));
    btnExportFile->Disable();
    auto btnAntiDebugging = new wxButton(sidebarPanel, wxID_ANY, "Anti-Debug");
    btnAntiDebugging->SetBitmap(Bitmap::CreateFromBuffer(iconNoPreview));
    btnAntiDebugging->Disable();
    auto btnObfuscation = new wxButton(sidebarPanel, wxID_ANY, "Obfuscation");
    btnObfuscation->SetBitmap(Bitmap::CreateFromBuffer(iconObfuscation));
    btnObfuscation->Disable();
    auto btnVirtualization = new wxButton(sidebarPanel, wxID_ANY, "Virtualization");
    btnVirtualization->SetBitmap(Bitmap::CreateFromBuffer(iconVirtualization));
    btnVirtualization->Disable();
    auto btnLicenseManager = new wxButton(sidebarPanel, wxID_ANY, "Licensing");
    btnLicenseManager->SetBitmap(Bitmap::CreateFromBuffer(iconLicensing));
    btnLicenseManager->Disable();
    auto btnHelp = new wxButton(sidebarPanel, wxID_ANY, "Help");

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
    SetStatusText("Welcome to BinArmor v0.1");

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

