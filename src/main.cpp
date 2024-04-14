#include "dynamiclinker/dynamiclinker.hpp"
#include "dynamiclinker/librarydumper.h"
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
        }
        std::cout << "===========================================================================" << std::endl;

        it++;
    }
};

int main() {
    CStdOutDumper* stdImportDumper = new CStdOutDumper();
    CDynamicLinker* pDynamicLinker = new CDynamicLinker();

    pDynamicLinker->LoadFunction("ntdll.dll", "NtQueryInformationProcess");

    pDynamicLinker->DumpLoaded(stdImportDumper);

    return 0;
}
