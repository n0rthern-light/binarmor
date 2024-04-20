#include <windows.h>
#include <iostream>
#include "services.hpp"
#include "../shared/win_api.hpp"
#include "../shared/RuntimeException.hpp"

#ifdef DEBUG
#include <cstdio>
#include "MemoryNavigator.hpp"

DWORD WINAPI DebugThreadFunction(void* data) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    std::cout << "Debug console allocated." << std::endl;

    uintptr_t hEntryBaseAddress;

    const char* modName = "target_x86.exe";
    hEntryBaseAddress = reinterpret_cast<uintptr_t>(gDynamicLinker->GetFunction(KERNEL32, KERNEL32_GetModuleHandleA)->call<pGetModuleHandleA>(modName));

    std::cout << "hEntryBaseAddress: " << std::hex << hEntryBaseAddress << std::endl;

    const char* pattern = "FF 8B 4B 18 6A 03 6A 00 6A 00";
    std::cout << "Searching for pattern: " << pattern << std::endl;

    try {
        auto address = gPatternScanner->FindPatternAddress(modName, pattern);
        std::cout << "Result = " << std::hex << address << " casted DWORD: " << std::hex << address << std::endl;
        /*
        auto addressOfPythonPlayerPtrVar = *reinterpret_cast<uintptr_t*>(address + 0x4);
        auto localPlayerAddress = *reinterpret_cast<uintptr_t*>(addressOfPythonPlayerPtrVar);
        std::cout << "Address of PythonPlayerPtrVar: " << std::hex << addressOfPythonPlayerPtrVar << " rva: " << std::hex << addressOfPythonPlayerPtrVar - hEntryBaseAddress << std::endl;
        std::cout << "localPlayerAddress: " << std::hex << localPlayerAddress << " rva: " << std::hex << localPlayerAddress - hEntryBaseAddress << std::endl;
        */
    } catch (RuntimeException e) {
        std::cout << "Exception occurredd!!!!" << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception occurredd!!!!111" << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unspecified exception occurereed!" << std::endl;
    }

    //MemoryNavigator::run();

    return 0;
}
#endif

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
#ifdef DEBUG
    HANDLE hDebugThread = nullptr;
#endif
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
        initServices();
#ifdef DEBUG
            MessageBox(NULL, "DLL Loaded", "Status", MB_OK | MB_ICONINFORMATION);
#endif
            DisableThreadLibraryCalls(hinstDLL);

#ifdef DEBUG
            hDebugThread = CreateThread(NULL, 0, DebugThreadFunction, NULL, 0, NULL);
            CloseHandle(hDebugThread);
#endif

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
