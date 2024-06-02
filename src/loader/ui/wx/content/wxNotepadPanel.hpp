#pragma once

#include "../wx_headers.hpp"
#include "core/file/BinaryFile.hpp"
#include "loader/ui/wx/content/wxBinaryFileInfoPanel.hpp"
#include <wx/generic/panelg.h>
#include <shared/message/IMessageBus.hpp>
#include <wx/sizer.h>
#include <wx/notebook.h>

class CwxNotepadPanel : public wxPanel
{
    IMessageBus* m_eventBus;
    std::shared_ptr<wxBoxSizer> m_sizer;
    std::shared_ptr<wxStaticText> m_fileName;
    std::shared_ptr<wxNotebook> m_notebook;
    std::shared_ptr<CwxBinaryFileInfoPanel> m_binaryFileInfoPanel;
    std::shared_ptr<wxSizer> m_binaryFileInfoPanelSizer;
public:
    CwxNotepadPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void loadFileData(const CBinaryFile& binaryFile);
};

