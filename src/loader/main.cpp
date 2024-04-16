#include "../shared/DynamicLinker.hpp"
#include "../shared/PatternScanner.hpp"
#include "../shared/strenc.hpp"
#include "../shared/win_api.hpp"
#include <iostream>

#ifdef DEBUG
static unsigned int it = 0;
class CStdOutDumper: public ILibraryDumper
{
    void dump(CLibrary* library)
    {
        std::cout << "#" << it << " -> " << library->name << " at: " << std::hex << library->baseAddress << std::endl;
        unsigned int f_it = 0;
        for (auto f : library->functions) {
            std::cout << "   " << "#" << f_it << " -> " << f.second->name << " at: " << std::hex << f.second->resolvedAddress << " rva: " << std::hex << f.second->rva << std::endl;
            f_it++;
        }
        std::cout << "============================================================================" << std::endl;

        it++;
    }
};
#endif

int main() {
#ifdef DEBUG
    CStdOutDumper* stdImportDumper = new CStdOutDumper();
#endif
    CDynamicLinker* pDynamicLinker = new CDynamicLinker();
    CPatternScanner* pPatternScanner = new CPatternScanner(pDynamicLinker);

    pDynamicLinker->LoadFunction(strenc("ntdll.dll"), strenc("NtQueryInformationProcess"));
    pDynamicLinker->LoadFunction(strenc("ntdll.dll"), strenc("NtAllocateVirtualMemory"));
    pDynamicLinker->LoadFunction(strenc("ntdll.dll"), strenc("NtFreeVirtualMemory"));
    pDynamicLinker->LoadFunction(strenc("ntdll.dll"), strenc("NtProtectVirtualMemory"));
    pDynamicLinker->LoadFunction(KERNEL32, KERNEL32_GetModuleInformation);

    auto result = pPatternScanner->FindPatternAddress("advanced-memory_debug.exe", "3D ?? ?? ?? ?? 77 4E");

    if (result > 0) {
        std::cout << "Pattern found at address: " << std::hex << result << std::endl;
        std::cout << "Testing if byte is equal" << std::endl;
        if (*(BYTE*)result == 61) {
            std::cout << "result OK" << std::endl;
        } else {
            std::cout << "result not ok - " << *(BYTE*)result << " != 61 (0x3D)" << std::endl;
        }
        if (*(BYTE*)(result + 5) == 119) {
            std::cout << "result OK" << std::endl;
        } else {
            std::cout << "result not ok - " << *(BYTE*)(result + 5) << " != 119 (0x77)" << std::endl;
        }
    } else {
        std::cout << "Address not found :-(" << std::endl;
    }


#ifdef DEBUG
    pDynamicLinker->DumpLoaded(stdImportDumper);
#endif

    return 0;
}
