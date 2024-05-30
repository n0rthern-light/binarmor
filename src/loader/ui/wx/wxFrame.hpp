#pragma once

#include "loader/ui/wx/wxContentPanel.hpp"
#include "loader/ui/wx/wxSidebarPanel.hpp"
#include "wx_headers.hpp"
#include <shared/event/IEventBus.hpp>
#include <core/file/BinaryFile.hpp>
#include <wx/generic/panelg.h>

class CwxFrame : public wxFrame
{
private:
	IEventBus* m_eventBus;
    std::unique_ptr<wxPanel> m_mainPanel;
    std::unique_ptr<CwxSidebarPanel> m_sidebarPanel;
    std::unique_ptr<CwxContentPanel> m_contentPanel;

	void initUi();
	void initEventListener();
	void onEventDisplayWindowOpenFile(wxCommandEvent& event);
public:
    CwxFrame(IEventBus* t_eventBus);
	void promptOpenFile();
	void displayStatus(const std::string& statusText);
	void displayBinaryFile(const CBinaryFile& binaryFile);
};
