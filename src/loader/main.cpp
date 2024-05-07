#include "headers.hpp"
#include "ui/contract.hpp"
#include "event/contract.hpp"

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    int argc;
    wchar_t** wargv = CommandLineToArgvW(GetCommandLineW(), &argc);
    char** argv = new char* [argc + 1];  // allocate space for argc + terminating NULL

    for (int i = 0; i < argc; ++i) {
        int len = wcslen(wargv[i]) + 1;
        argv[i] = new char[len];
        wcstombs(argv[i], wargv[i], len);
    }
    argv[argc] = NULL;  // NULL terminate the array
    LocalFree(wargv);

    // ----------------

    event::init();
    event::bus->subscribe(typeid(TestEvent), [](IEvent* event) {
        auto dupaEvent = dynamic_cast<TestEvent*>(event);
        MessageBoxA(0, dupaEvent->str.c_str(), "Information", 0);
    });
	ui::init(argc, argv);

    // ----------------

    for (int i = 0; i < argc; ++i) {
        delete[] argv[i];
    }
    delete[] argv;

	return 0;
}
#endif

