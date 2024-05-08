#include "wxWidgetsGuiApp.hpp"

CwxWidgetsGuiApp::CwxWidgetsGuiApp(int argc, char** argv)
{
    app = new CwxApp();
    wxApp::SetInstance(app);
    app->CallOnInit();

    wxEntryStart(argc, argv);

    frame = new CwxFrame();
    frame->Show(true);

    app->OnRun();
    app->OnExit();

    wxEntryCleanup();
}

void CwxWidgetsGuiApp::exit()
{
    app->Exit();
}
