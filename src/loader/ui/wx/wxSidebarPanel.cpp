#include "wxSidebarPanel.hpp"
#include "bitmap.hpp"
#include "../icons.hpp"
#include "../../application/events/UIRequestedOpenFileEvent.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <memory>

CwxSidebarPanel::CwxSidebarPanel(wxWindow* parent, IMessageBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;

    this->SetMinSize(wxSize(180, 400));
    m_sizer = std::make_unique<wxBoxSizer>(wxVERTICAL);
    this->SetSizer(m_sizer.get());

    m_btnOpenFile = std::make_shared<wxButton>(this, wxID_ANY, strenc("Open File"));
    m_btnOpenFile->SetBitmap(Bitmap::CreateFromBuffer(iconOpenFile));
    m_btnOpenFile->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
        m_eventBus->publish(new CUIRequestedOpenFileEvent());
    });

    m_btnExportFile = std::make_shared<wxButton>(this, wxID_ANY, strenc("Export File"));
    m_btnExportFile->SetBitmap(Bitmap::CreateFromBuffer(iconExport));
    m_btnExportFile->Disable();

    m_btnAntiDebugging = std::make_shared<wxButton>(this, wxID_ANY, strenc("Anti-Debug"));
    m_btnAntiDebugging->SetBitmap(Bitmap::CreateFromBuffer(iconNoPreview));
    m_btnAntiDebugging->Disable();

    m_btnObfuscation = std::make_shared<wxButton>(this, wxID_ANY, strenc("Obfuscation"));
    m_btnObfuscation->SetBitmap(Bitmap::CreateFromBuffer(iconObfuscation));
    m_btnObfuscation->Disable();

    m_btnVirtualization = std::make_shared<wxButton>(this, wxID_ANY, strenc("Virtualization"));
    m_btnVirtualization->SetBitmap(Bitmap::CreateFromBuffer(iconVirtualization));
    m_btnVirtualization->Disable();

    m_btnLicenseManager = std::make_shared<wxButton>(this, wxID_ANY, strenc("Licensing"));
    m_btnLicenseManager->SetBitmap(Bitmap::CreateFromBuffer(iconLicensing));
    m_btnLicenseManager->Disable();

    m_btnHelp = std::make_shared<wxButton>(this, wxID_ANY, strenc("Help"));

    m_sizer->Add(m_btnOpenFile.get(), 0, wxEXPAND | wxALL, 5);
    m_sizer->AddSpacer(15);
    m_sizer->Add(m_btnAntiDebugging.get(), 0, wxEXPAND | wxALL, 5);
    m_sizer->Add(m_btnObfuscation.get(), 0, wxEXPAND | wxALL, 5);
    m_sizer->Add(m_btnVirtualization.get(), 0, wxEXPAND | wxALL, 5);
    m_sizer->Add(m_btnLicenseManager.get(), 0, wxEXPAND | wxALL, 5);
    m_sizer->AddStretchSpacer(1);
    m_sizer->Add(m_btnExportFile.get(), 0, wxEXPAND | wxALL, 5);
    m_sizer->Add(m_btnHelp.get(), 0, wxEXPAND | wxALL, 5);

    lockFeatureButtons();
} 

std::vector<std::shared_ptr<wxButton>>CwxSidebarPanel::featureButtons()
{
    return std::vector {
        m_btnAntiDebugging,
        m_btnObfuscation,
        m_btnVirtualization,
        m_btnLicenseManager,
    };
}

void CwxSidebarPanel::lockFeatureButtons()
{
    for(const auto& btn : featureButtons()) {
        btn->Disable();
    }
}

void CwxSidebarPanel::unlockFeatureButtons()
{
    for(const auto& btn : featureButtons()) {
        btn->Enable();
    }
}

