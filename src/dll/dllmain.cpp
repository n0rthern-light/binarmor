#include <windows.h>
#include <iostream>
#include "../shared/DynamicLinker.hpp"

#ifdef DEBUG
#include <cstdio>
#endif

DWORD WINAPI ThreadFunc(void* data) {
    DWORD hEntryBaseAddress;

    hEntryBaseAddress = (DWORD)GetModuleHandleA("metin2client.exe");
    std::cout << "hEntryBaseAddress: " << std::hex << hEntryBaseAddress << std::endl;

    auto linker = new CDynamicLinker();
    (void**)linker;

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    HANDLE hThread = nullptr;
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
#ifdef DEBUG
            MessageBox(NULL, "DLL Loaded", "Status", MB_OK | MB_ICONINFORMATION);
            AllocConsole();
            freopen("CONOUT$", "w", stdout);
            std::cout << "Debug console allocated." << std::endl;
#endif
            DisableThreadLibraryCalls(hinstDLL);

            hThread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
            CloseHandle(hThread);

            break;
        case DLL_PROCESS_DETACH:
#ifdef DEBUG
            FreeConsole();
            MessageBox(NULL, "DLL Unloaded", "Status", MB_OK | MB_ICONINFORMATION);
#endif
            break;
    }
    return TRUE;
}
