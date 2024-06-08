#include "wxBinaryFileInfoPanel.hpp"
#include "core/attributes.hpp"
#include "loader/ui/wx/wx_headers.hpp"
#include "shared/RuntimeException.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include "shared/value/Unsigned.hpp"

CwxBinaryFileInfoPanel::CwxBinaryFileInfoPanel(wxWindow* parent, IMessageBus* t_eventBus) : wxPanel(parent, wxID_ANY)
{
    m_eventBus = t_eventBus;
    m_sizer = std::make_unique<wxBoxSizer>(wxVERTICAL);

    initInfoRows();
    updateWxInfoRows();

    SetSizer(m_sizer.get());
}

void CwxBinaryFileInfoPanel::initInfoRows()
{
    m_infoRows = { };

    m_infoRows[0] = TextInfoRow_t { strenc("binary_path"), strenc("Full Path:"), strenc("") };
    m_infoRows[1] = TextInfoRow_t { strenc("binary_hash"), strenc("Checksum:"), strenc("") };
    m_infoRows[2] = TextInfoRow_t { strenc("binary_platform"), strenc("Platform:"), strenc("") };
    m_infoRows[3] = TextInfoRow_t { strenc("binary_arch"), strenc("Architecture:"), strenc("") };
    m_infoRows[4] = TextInfoRow_t { strenc("binary_type"), strenc("Type:"), strenc("") };
    m_infoRows[5] = TextInfoRow_t { strenc("binary_section_count"), strenc("Sections:"), strenc("") };
    m_infoRows[6] = TextInfoRow_t { strenc("binary_import_module_count"), strenc("Imported Modules:"), strenc("") };
    m_infoRows[7] = TextInfoRow_t { strenc("binary_import_function_count"), strenc("Imported Functions:"), strenc("") };
    m_infoRows[8] = TextInfoRow_t { strenc("binary_entry_point"), strenc("Entry Point:"), strenc("") };
    m_infoRows[9] = TextInfoRow_t { strenc("binary_size_total"), strenc("Size of the Binary:"), strenc("") };
    m_infoRows[10] = TextInfoRow_t { strenc("binary_size_code"), strenc("Size of Code:"), strenc("") };
    m_infoRows[11] = TextInfoRow_t { strenc("binary_protection_state"), strenc("State of protection:"), strenc("") };
}

int CwxBinaryFileInfoPanel::resolveKey(const std::string& id)
{
    for (const auto& row : m_infoRows) {
        if (row.second.id == id) {
            return row.first;
        }
    }

    return -1;
}

void CwxBinaryFileInfoPanel::setInfo(const std::string& key, const std::string& value)
{
    m_infoRows[resolveKey(key)].value = value;
}

void CwxBinaryFileInfoPanel::updateWxInfoRows()
{
    m_sizer->Clear(true);

    for (const auto& row : m_infoRows) {
        m_sizer->Add(createInfoRow(row.second), 0, wxEXPAND | wxALL, 3);
    }

    Layout();
}

wxBoxSizer* CwxBinaryFileInfoPanel::createInfoRow(const TextInfoRow_t& row)
{
    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    auto label = new wxStaticText(this, wxID_ANY, row.label);
    auto value = new wxStaticText(this, wxID_ANY, row.value);

    sizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer->Add(value, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    return sizer;
}

void CwxBinaryFileInfoPanel::loadFileData(const CBinaryFile& binaryFile)
{
    setInfo(strenc("binary_path"), binaryFile.filePath().string().c_str());

    const auto attributes = binaryFile.attributes();
    setInfo(strenc("binary_hash"), attributes.hash);

    switch (binaryFile.format()) {
        case Format::Windows_PE:
            setInfo(strenc("binary_platform"), strenc("Windows"));
        break;
        case Format::MacOS_MachO:
            setInfo(strenc("binary_platform"), strenc("MacOS"));
        break;
        case Format::Linux_ELF:
            setInfo(strenc("binary_platform"), strenc("Linux"));
        break;
        default:
            throw RuntimeException(strenc("Unhandled format to display"));
        break;
    };

    switch (attributes.arch) {
        case Architecture::ARM:
            setInfo(strenc("binary_arch"), strenc("arm"));
        break;
        case Architecture::ARM64:
            setInfo(strenc("binary_arch"), strenc("arm64"));
        break;
        case Architecture::X86:
            setInfo(strenc("binary_arch"), strenc("x86"));
        break;
        case Architecture::X86_64:
            setInfo(strenc("binary_arch"), strenc("x86_64"));
        break;
        case Architecture::UNIVERSAL:
            setInfo(strenc("binary_arch"), strenc("Universal (FAT)"));
        break;
        default:
            throw RuntimeException(strenc("Unhandled architecture to display"));
        break;
    }

    switch (attributes.type) {
        case Type::Executable:
            setInfo(strenc("binary_type"), strenc("Executable"));
        break;
        case Type::Dynamic_Library:
            setInfo(strenc("binary_type"), strenc("Dynamic Library"));
        break;
        default:
            throw RuntimeException(strenc("Unhandled type to display"));
        break;
    }

    setInfo(strenc("binary_section_count"), CUnsigned{ as_32(attributes.sectionCount) }.asDecimalString());
    setInfo(strenc("binary_import_module_count"), CUnsigned{ as_32(attributes.importedModuleCount) }.asDecimalString());
    setInfo(strenc("binary_import_function_count"), CUnsigned{ as_32(attributes.importedFunctionsCount) }.asDecimalString());
    setInfo(strenc("binary_entry_point"), attributes.entryPoint.asShortHexString());
    setInfo(strenc("binary_size_total"), attributes.sizeOfBinary.asShortHexString());
    setInfo(strenc("binary_size_code"), attributes.sizeOfCode.asShortHexString());
    setInfo(strenc("binary_protection_state"), attributes.isProtected ? strenc("Protected by BinArmor") : strenc("Not protected"));
    
    updateWxInfoRows();
}

