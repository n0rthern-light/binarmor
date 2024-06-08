#ifndef LOADER_UI_WX_CONTENT_WX_NOTEPAD_PANEL_HPP_
#define LOADER_UI_WX_CONTENT_WX_NOTEPAD_PANEL_HPP_

#include "../wx_headers.hpp"
#include "core/file/BinaryFile.hpp"
#include "loader/ui/wx/content/wxBinaryFileInfoPanel.hpp"
#include <shared/message/IMessageBus.hpp>

class CwxNotepadPanel : public wxPanel
{
    IMessageBus* m_eventBus;
    std::unique_ptr<wxBoxSizer> m_sizer;
    std::unique_ptr<wxStaticText> m_fileName;
    std::unique_ptr<wxNotebook> m_notebook;
    std::unique_ptr<CwxBinaryFileInfoPanel> m_binaryFileInfoPanel;
    std::unique_ptr<wxSizer> m_binaryFileInfoPanelSizer;
public:
    CwxNotepadPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void loadFileData(const CBinaryFile& binaryFile);
};

#endif // LOADER_UI_WX_CONTENT_WX_NOTEPAD_PANEL_HPP_
