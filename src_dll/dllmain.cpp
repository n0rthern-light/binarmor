#include <windows.h>

extern "C" __declspec(dllexport) void ShowGreeting() {
    MessageBox(NULL, "Hi!!", "Greeting", MB_OK | MB_ICONINFORMATION);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            MessageBox(NULL, "DLL Loaded", "Status", MB_OK | MB_ICONINFORMATION);
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            MessageBox(NULL, "DLL Unloaded", "Status", MB_OK | MB_ICONINFORMATION);
            break;
    }
    if (lpReserved) {
        goto end;
    }

    end:
    return TRUE;
}
