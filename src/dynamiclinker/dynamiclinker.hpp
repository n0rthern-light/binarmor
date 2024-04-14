#ifndef DYNAMICLINKER_H
#define DYNAMICLINKER_H

#include "../includes/winapi_typedefs.h"
#include "librarydumper.h"
#include <vector>
#include <map>
#include <string>

struct Function {
    std::string name;
    DWORD rva;
    PVOID resolvedAddress;
};

class CLibrary
{
public:
    std::string name;
    PVOID baseAddress;
    std::map<std::string, Function*> functions;

    CLibrary(const std::string& name, PVOID baseAddress);
    bool HasFunction(const char* functionName);
    void LoadFunction(const char* functionName);
    Function* GetFunction(const char* functionName);
};

class CDynamicLinker
{
    std::map<std::string, CLibrary*> libraries;
    CLibrary* kernel32;

    PPEB GetPEB();
    PVOID FindLoadedLibraryBaseAddress(const char* moduleName);
    void LoadKernel32();
    bool IsKernel32LibraryResolved();
    bool HasLibrary(const char* moduleName);
    void MarkLibraryLoaded(const char* moduleName);
    void LoadLibraryMod(const char* moduleName);
public:
    CDynamicLinker();
    void LoadFunction(const char* moduleName, const char* functionName);
    Function* GetFunction(const char* moduleName, const char* functionName);
    void DumpLoaded(ILibraryDumper* dumper);
};

#endif