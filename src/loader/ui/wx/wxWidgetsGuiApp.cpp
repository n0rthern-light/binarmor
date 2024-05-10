#include "wxWidgetsGuiApp.hpp"

CwxWidgetsGuiApp::CwxWidgetsGuiApp(int _argc, char** _argv, IEventBus* _eventBus)
{
    argc = _argc;
    argv = _argv;
    eventBus = _eventBus;

    app = new CwxApp();
    wxApp::SetInstance(app);
    app->CallOnInit();
    frame = new CwxFrame(eventBus);
}

void CwxWidgetsGuiApp::start()
{
    wxEntryStart(argc, argv);
    frame->Show(true);
    app->OnRun();
    app->OnExit();
    wxEntryCleanup();
}

void CwxWidgetsGuiApp::promptOpenFile()
{
    frame->promptOpenFile();
}

void CwxWidgetsGuiApp::exit()
{
    app->Exit();
}
