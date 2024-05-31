#pragma once

#include "../wx_headers.hpp"
#include "core/file/BinaryFile.hpp"
#include <wx/generic/panelg.h>
#include <shared/message/IMessageBus.hpp>
#include <wx/sizer.h>

class CwxBinaryFileInfoPanel : public wxPanel
{
    IMessageBus* m_eventBus;
    std::unique_ptr<wxBoxSizer> m_sizer;

    wxBoxSizer* createInfoRow(const wxString& label, const wxString& value);
public:
    CwxBinaryFileInfoPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void showFile(const CBinaryFile& binaryFile);
};

