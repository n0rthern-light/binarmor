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

    auto result = pPatternScanner->FindPatternAddress("advanced-memory_debug.exe", "FF 83 F0 01 84 C0 74 28 48 8B 45 20 48 89 C1 E8 88 F7 FF FF EB 1A 48 89 C3 48 8B 45 20 48 89 C1 E8 3B 39 0A 00 48 89 D8 48 89 C1 E8 70 BE 00 00 90 48 83 C4 58 5B 5D C3 55 53 48 83 EC 58 48 8D");

    if (result > 0) {
        std::cout << "Pattern found at address: " << std::hex << result << std::endl;
    } else {
        std::cout << "Address not found :-(" << std::endl;
    }


#ifdef DEBUG
    pDynamicLinker->DumpLoaded(stdImportDumper);
#endif

    return 0;
}
