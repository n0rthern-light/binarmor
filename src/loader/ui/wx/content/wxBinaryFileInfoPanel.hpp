#pragma once

#include "../wx_headers.hpp"
#include "core/file/BinaryFile.hpp"
#include <wx/generic/panelg.h>
#include <shared/message/IMessageBus.hpp>
#include <wx/sizer.h>
#include <map>

struct TextInfoRow_t
{
    std::string label;
    std::string value;
};

class CwxBinaryFileInfoPanel : public wxPanel
{
    IMessageBus* m_eventBus;
    std::shared_ptr<wxBoxSizer> m_sizer;
    std::map<std::string, TextInfoRow_t> m_infoRows;

    void initInfoRows();
    std::string resolveKey(const std::string& baseKey);
    void setLabel(const std::string& key, const std::string& label);
    void setInfo(const std::string& key, const std::string& value);
    void updateWxInfoRows();
    wxBoxSizer* createInfoRow(const wxString& label, const wxString& value);
public:
    CwxBinaryFileInfoPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void loadFileData(const CBinaryFile& binaryFile);
};

