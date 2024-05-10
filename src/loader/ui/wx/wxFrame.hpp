#pragma once

#include "wx_headers.hpp"
#include <shared/event/IEventBus.hpp>

class CwxFrame : public wxFrame
{
private:
	IEventBus* eventBus;

	void initUi();
public:
    CwxFrame(IEventBus* _eventBus);
	void promptOpenFile();
};

