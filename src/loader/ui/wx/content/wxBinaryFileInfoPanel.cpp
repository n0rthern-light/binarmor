#include "wxBinaryFileInfoPanel.hpp"
#include "loader/ui/wx/wx_headers.hpp"
#include "shared/RuntimeException.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include "shared/value/Unsigned.hpp"

CwxBinaryFileInfoPanel::CwxBinaryFileInfoPanel(wxWindow* parent, IMessageBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;

    m_sizer = std::make_unique<wxBoxSizer>(wxVERTICAL);

    this->SetSizer(m_sizer.get());
}

wxBoxSizer* CwxBinaryFileInfoPanel::createInfoRow(const wxString& label, const wxString& value)
{
    auto sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(new wxStaticText(this, wxID_ANY, label), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer->Add(new wxStaticText(this, wxID_ANY, value), 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    return sizer;
}

void CwxBinaryFileInfoPanel::showFile(const CBinaryFile& binaryFile)
{
    m_sizer->Clear(true);

    m_sizer->Add(createInfoRow(strenc("Name of the Binary:"), binaryFile.filePath()), 0, wxEXPAND | wxALL, 2);

    // Hash (checksum)
    m_sizer->Add(createInfoRow(strenc("Hash (Checksum):"), binaryFile.binary().hash()), 0, wxEXPAND | wxALL, 2);

    switch (binaryFile.format()) {
        case Format::Windows_PE:
            m_sizer->Add(createInfoRow(strenc("Target Platform:"), strenc("Windows")), 0, wxEXPAND | wxALL, 2);
        break;
        case Format::MacOS_MachO:
            m_sizer->Add(createInfoRow(strenc("Target Platform:"), strenc("MacOS")), 0, wxEXPAND | wxALL, 2);
        break;
        case Format::Linux_ELF:
            m_sizer->Add(createInfoRow(strenc("Target Platform:"), strenc("Linux")), 0, wxEXPAND | wxALL, 2);
        break;
        default:
            throw RuntimeException(strenc("Unhandled format to display"));
        break;
    };

    m_sizer->Add(createInfoRow(strenc("Architecture:"), "x86_64"), 0, wxEXPAND | wxALL, 2);

    m_sizer->Add(createInfoRow(strenc("Size of Code Sections:"), CUnsigned((uint_64)binaryFile.binary().size()).asShortHexString()), 0, wxEXPAND | wxALL, 2);

    m_sizer->Add(createInfoRow(strenc("State of protection:"), "Not protected by BinArmor"));
    
    Layout();
}

