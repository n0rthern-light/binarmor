#include "dynamiclinker/dynamiclinker.hpp"
#include "dynamiclinker/librarydumper.hpp"
#include "includes/no_strings.hpp"
#include <iostream>

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
        std::cout << "===========================================================================" << std::endl;

        it++;
    }
};

int main() {
    CStdOutDumper* stdImportDumper = new CStdOutDumper();
    CDynamicLinker* pDynamicLinker = new CDynamicLinker();

    pDynamicLinker->LoadFunction(strenc("ntdll.dll"), strenc("NtQueryInformationProcess"));
    pDynamicLinker->LoadFunction(strenc("ntdll.dll"), strenc("NtAllocateVirtualMemory"));
    pDynamicLinker->LoadFunction(strenc("ntdll.dll"), strenc("NtFreeVirtualMemory"));
    pDynamicLinker->LoadFunction(strenc("ntdll.dll"), strenc("NtProtectVirtualMemory"));

    pDynamicLinker->DumpLoaded(stdImportDumper);

    return 0;
}
