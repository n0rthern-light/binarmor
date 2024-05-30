#pragma once

#include "../wx_headers.hpp"
#include "core/file/BinaryFile.hpp"
#include <wx/generic/panelg.h>
#include <shared/event/IEventBus.hpp>
#include <wx/sizer.h>

class CwxBinaryFileInfoPanel : public wxPanel
{
    IEventBus* m_eventBus;
    std::unique_ptr<wxBoxSizer> m_sizer;

    wxBoxSizer* createInfoRow(const wxString& label, const wxString& value);
public:
    CwxBinaryFileInfoPanel(wxWindow* parent, IEventBus* t_eventBus);
    void showFile(const CBinaryFile& binaryFile);
};

