#pragma once

#include "wx_headers.hpp"
#include <shared/event/IEventBus.hpp>
#include <core/file/Binary.hpp>

class CwxFrame : public wxFrame
{
private:
	IEventBus* eventBus;
	wxTextCtrl* binaryDisplay;

	void initUi();
	void initEventListener();
	void onEventDisplayWindowOpenFile(wxCommandEvent& event);
public:
  CwxFrame(IEventBus* _eventBus);
	void promptOpenFile();
	void displayStatus(const std::string& statusText);
	void displayBinary(const CBinary& binary);
};
