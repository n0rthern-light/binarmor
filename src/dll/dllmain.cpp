#include <windows.h>
#include <iostream>
#include "services.hpp"
#include "../shared/win_api.hpp"
#include "../shared/RuntimeException.hpp"

#ifdef DEBUG
#include <cstdio>
#endif

DWORD WINAPI ThreadFunc(void* data) {
    DWORD hEntryBaseAddress;

    const char* modName = "metin2client.exe";
    hEntryBaseAddress = (DWORD)gDynamicLinker->GetFunction(KERNEL32, KERNEL32_GetModuleHandleA)->call<pGetModuleHandleA>(modName);
    std::cout << "hEntryBaseAddress: " << std::hex << hEntryBaseAddress << std::endl;

    const char* pattern = "89 15 ?? ?? ?? ?? C7 45 FC 00 00 00 00 8B 45 F0 83 C0 04 89 45 C8";
    std::cout << "Searching for pattern: " << pattern << std::endl;

    try {
        auto address = gPatternScanner->FindPatternAddress(modName, pattern);
        std::cout << "Result = " << std::hex << address << " casted DWORD: " << std::hex << (DWORD)address << std::endl;
    } catch (RuntimeException e) {
        std::cout << "Exception occurredd!!!!" << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception occurredd!!!!111" << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unspecified exception occurereed!" << std::endl;
    }

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    HANDLE hThread = nullptr;
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
        initServices();
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
