#ifndef LOADER_UI_WX_CONTENT_WX_NOTEPAD_PANEL_HPP_
#define LOADER_UI_WX_CONTENT_WX_NOTEPAD_PANEL_HPP_

#include "../wx_headers.hpp"
#include "core/file/BinaryFile.hpp"
#include "loader/ui/wx/content/wxBinaryFileInfoPanel.hpp"
#include <shared/message/IMessageBus.hpp>

class CwxNotepadPanel : public wxPanel
{
    program::shared::message::IMessageBus* m_eventBus;
    wxBoxSizer* m_sizer;
    wxStaticText* m_fileName;
    wxNotebook* m_notebook;
    CwxBinaryFileInfoPanel* m_binaryFileInfoPanel;
    wxSizer* m_binaryFileInfoPanelSizer;
public:
    CwxNotepadPanel(wxWindow* parent, program::shared::message::IMessageBus* t_eventBus);
    void loadFileData(const program::core::file::CBinaryFile& binaryFile);
};

#endif // LOADER_UI_WX_CONTENT_WX_NOTEPAD_PANEL_HPP_
