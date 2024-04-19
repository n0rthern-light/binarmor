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

    const char* pattern = "8B 45 E0 A3 ?? ?? ?? ?? 8B 4D E0";
    std::cout << "Searching for pattern: " << pattern << std::endl;

    try {
        auto address = gPatternScanner->FindPatternAddress(modName, pattern);
        std::cout << "Result = " << std::hex << address << " casted DWORD: " << std::hex << (DWORD)address << std::endl;
        DWORD addressOfPythonPlayerPtrVar = *reinterpret_cast<DWORD*>(address + 0x4);
        DWORD localPlayerAddress = *reinterpret_cast<DWORD*>(addressOfPythonPlayerPtrVar);
        std::cout << "Address of PythonPlayerPtrVar: " << std::hex << addressOfPythonPlayerPtrVar << " rva: " << std::hex << addressOfPythonPlayerPtrVar - hEntryBaseAddress << std::endl;
        std::cout << "localPlayerAddress: " << std::hex << localPlayerAddress << " rva: " << std::hex << localPlayerAddress - hEntryBaseAddress << std::endl;
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
