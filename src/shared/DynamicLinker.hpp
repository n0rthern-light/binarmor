#ifndef DYNAMICLINKER_H
#define DYNAMICLINKER_H

#include <Windows.h>
#include <vector>
#include <map>
#include <string>

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWCH   Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _LDR_DATA_TABLE_ENTRY {
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _PEB_LDR_DATA {
    ULONG Length;
    BOOLEAN Initialized;
    PVOID SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _PEB {
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    BOOLEAN SpareBool;
    HANDLE Mutant;
    PVOID ImageBaseAddress;
    PPEB_LDR_DATA Ldr;
} PEB, *PPEB;

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

class ILibraryDumper
{
public:
    virtual ~ILibraryDumper() = default;
    virtual void dump(CLibrary* library) = 0;
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