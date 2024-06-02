#pragma once
#include <core/file/BinaryFile.hpp>
#include <string>

class IGuiApp
{
public:
	virtual ~IGuiApp() {};
	virtual void start() {};
	virtual void promptOpenFile() = 0;
	virtual void displayErrorMessageBox(const std::string& title, const std::string& message) = 0;
	virtual void displayInfoMessageBox(const std::string& title, const std::string& message) = 0;
	virtual void displayStatus(const std::string& statusText) = 0;
	virtual void displayBinaryFile(const CBinaryFile& binary) = 0;
    virtual void appendToLoadedFiles(const CBinaryFile* binary) = 0;
	virtual void exit() {};
};

