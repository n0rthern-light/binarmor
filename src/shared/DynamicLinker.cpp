#include "DynamicLinker.hpp"
#include "RuntimeException.hpp"
#include "strenc.hpp"
#include "win_api.hpp"
#include <wchar.h>
#include <cwchar>

wchar_t* charToWChar(const char* input) {
    std::setlocale(LC_ALL, ""); // Ensure the locale is set
    size_t len = std::mbstowcs(nullptr, input, 0) + 1; // Calculate the necessary length
    wchar_t* wstr = new wchar_t[len];
    std::mbstowcs(wstr, input, len);
    return wstr;
}

bool caseInsensitiveWStrCmp(const wchar_t* a, const wchar_t* b) {
    return _wcsicmp(a, b) == 0;
}

CLibrary::CLibrary(const std::string& name, PVOID baseAddress)
{
    this->name = name;
    this->baseAddress = baseAddress;
    this->functions = std::map<std::string, Function*>{};
}

bool CLibrary::HasFunction(const char* functionName)
{
    return this->functions.find(std::string(functionName)) != this->functions.end();
}

void CLibrary::LoadFunction(const char* functionName)
{
    if (this->HasFunction(functionName)) {
        return;
    }

    auto dosHeader = (PIMAGE_DOS_HEADER)this->baseAddress;
    auto ntHeaders = (PIMAGE_NT_HEADERS)((DWORD_PTR)this->baseAddress + dosHeader->e_lfanew);

    auto exportDirRVA = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    auto exportDir = (PIMAGE_EXPORT_DIRECTORY)((DWORD_PTR)this->baseAddress + exportDirRVA);

    auto namesRVA = (DWORD*)((DWORD_PTR)this->baseAddress + exportDir->AddressOfNames);
    auto ordinalsRVA = (WORD*)((DWORD_PTR)this->baseAddress + exportDir->AddressOfNameOrdinals);
    auto functionsRVA = (DWORD*)((DWORD_PTR)this->baseAddress + exportDir->AddressOfFunctions);

    for (DWORD i = 0; i < exportDir->NumberOfNames; i++) {
        const char* name = (const char*)((DWORD_PTR)this->baseAddress + namesRVA[i]);
        if (strcmp(name, functionName) == 0) {
            WORD ordinal = ordinalsRVA[i];
            DWORD functionRVA = functionsRVA[ordinal];

            auto address = (PVOID)((DWORD_PTR)this->baseAddress + functionRVA);
            auto strFunctionName = std::string(functionName);

            this->functions.emplace(strFunctionName, new Function {strFunctionName, functionRVA, address});

            return;
        }
    }

    throw RuntimeException(strenc("Failed to LoadFunction: ") + std::string(functionName));
}

Function* CLibrary::GetFunction(const char* functionName)
{
    if (!this->HasFunction(functionName)) {
        this->LoadFunction(functionName);
    }

    return this->functions[std::string(functionName)];
}

PPEB CDynamicLinker::GetPEB()
{
    PPEB peb;

    #ifdef _WIN64
        __asm__(strenc("mov %%gs:0x60, %0") : strenc("=r") (peb));
    #else
        __asm__(strenc("mov %%fs:0x30, %0") : strenc("=r") (peb));
    #endif

    return peb;
}

PVOID CDynamicLinker::FindLoadedLibraryBaseAddress(const char* moduleName)
{
    PPEB peb = (PPEB)this->GetPEB();
    PLIST_ENTRY head = &peb->Ldr->InLoadOrderModuleList;
    PLIST_ENTRY curr = head->Flink;

    while (curr != head) {
        PLDR_DATA_TABLE_ENTRY entry = CONTAINING_RECORD(curr, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
        if (caseInsensitiveWStrCmp(entry->BaseDllName.Buffer, charToWChar(moduleName))) {
            return (PVOID)entry->DllBase;
        }
        curr = curr->Flink;
    }

    throw RuntimeException(strenc("Failed to find already loaded library"));
}

void CDynamicLinker::LoadKernel32()
{
    PVOID kernel32Address;
    try {
        kernel32Address = this->FindLoadedLibraryBaseAddress(KERNEL32);
    } catch (RuntimeException) {
        throw RuntimeException(strenc("Failed to load kernel32"));
    }

    this->kernel32 = new CLibrary(KERNEL32, kernel32Address);
    this->kernel32->LoadFunction(KERNEL32_GetModuleHandleA);
    this->kernel32->LoadFunction(KERNEL32_GetProcAddress);
    this->kernel32->LoadFunction(KERNEL32_LoadLibraryA);

    this->libraries.emplace(this->kernel32->name, this->kernel32);
}

bool CDynamicLinker::IsKernel32LibraryResolved()
{
    return this->kernel32 != nullptr &&
        this->HasLibrary(KERNEL32);
}

bool CDynamicLinker::HasLibrary(const char* moduleName)
{
    return this->libraries.find(std::string(moduleName)) != this->libraries.end();
}

void CDynamicLinker::MarkLibraryLoaded(const char* moduleName)
{
    if (this->HasLibrary(moduleName)) {
        throw RuntimeException(strenc("Library already initialized!"));
    }

    auto baseAddress = this->FindLoadedLibraryBaseAddress(moduleName);

    auto strModuleName = std::string(moduleName);
    this->libraries.emplace(strModuleName, new CLibrary(strModuleName, baseAddress));
}

void CDynamicLinker::LoadLibraryMod(const char* moduleName)
{
    if (!this->IsKernel32LibraryResolved()) {
        throw RuntimeException(strenc("Kernel32 is required to load library"));
    }

    if (!this->kernel32->HasFunction(KERNEL32_LoadLibraryA)) {
        throw RuntimeException(strenc("Load library is required for this method"));
    }

    auto loadLibraryFn = this->kernel32->GetFunction(KERNEL32_LoadLibraryA);
    auto handle = loadLibraryFn->call<pLoadLibraryA>(moduleName);

    if (!handle) {
        throw RuntimeException(strenc("LoadLibrary API function failed!"));
    }

    this->MarkLibraryLoaded(moduleName);
}

CDynamicLinker::CDynamicLinker()
{
    this->kernel32 = nullptr;
    this->libraries = std::map<std::string, CLibrary*> {};

    if (!this->IsKernel32LibraryResolved()) {
        this->LoadKernel32();
    }
}

void CDynamicLinker::LoadFunction(const char* moduleName, const char* functionName)
{
    if (strcmp(moduleName, KERNEL32) == 0) {
        this->kernel32->LoadFunction(functionName);
        return;
    }

    if (!this->HasLibrary(moduleName)) {
        this->LoadLibraryMod(moduleName);
    }

    this->libraries[moduleName]->LoadFunction(functionName);
}

Function* CDynamicLinker::GetFunction(const char* moduleName, const char* functionName)
{
    if (strcmp(moduleName, KERNEL32) == 0) {
        return this->kernel32->GetFunction(functionName);
    }

    if (!this->HasLibrary(moduleName)) {
        this->LoadLibraryMod(moduleName);
    }

    return this->libraries[moduleName]->GetFunction(functionName);
}

void CDynamicLinker::DumpLoaded(ILibraryDumper* dumper)
{
    for(auto l : this->libraries) {
        dumper->dump(l.second);
    }
}