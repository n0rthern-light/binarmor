#pragma once
#include <string>
#include <core/Binary.hpp>

class IGuiApp
{
public:
	virtual ~IGuiApp() {};
	virtual void start() {};
	virtual void promptOpenFile() = 0;
	virtual void displayErrorMessageBox(const std::string& title, const std::string& message) = 0;
	virtual void displayInfoMessageBox(const std::string& title, const std::string& message) = 0;
	virtual void displayStatus(const std::string& statusText) = 0;
	virtual void displayBinary(const CBinary& binary) = 0;
	virtual void exit() {};
};
