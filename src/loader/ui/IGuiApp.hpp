#pragma once

class IGuiApp
{
public:
	virtual ~IGuiApp() {};
	virtual void start() {};
	virtual void promptOpenFile() = 0;
	virtual void exit() {};
};
