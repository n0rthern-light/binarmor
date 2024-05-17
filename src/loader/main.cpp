#include "headers.hpp"
#include "container.hpp"

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

    container::init(argc, argv);
    container::guiApp->start();

    // ----------------

    for (int i = 0; i < argc; ++i) {
        delete[] argv[i];
    }
    delete[] argv;

	return 0;
}
#else
int main(int argc, char** argv)
{
  container::init(argc, argv);
  container::guiApp->start();

  return 0;
}
#endif

