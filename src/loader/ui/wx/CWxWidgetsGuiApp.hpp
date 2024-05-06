#pragma once

#include "../IGuiApp.hpp"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
};

class CWxWidgetsGuiApp : public IGuiApp
{
	MyApp* app;
	MyFrame* frame;

public:
	CWxWidgetsGuiApp(int argc, char** argv);
	~CWxWidgetsGuiApp();
};

