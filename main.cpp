#include <windows.h>
#include <iostream>

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

typedef HMODULE(WINAPI* pGetModuleHandleA)(LPCSTR);
typedef FARPROC(WINAPI* pGetProcAddress)(HMODULE, LPCSTR);

FARPROC GetFunctionAddress(void* dllBase, const char* functionName) {
    auto dosHeader = (PIMAGE_DOS_HEADER)dllBase;
    auto ntHeaders = (PIMAGE_NT_HEADERS)((DWORD_PTR)dllBase + dosHeader->e_lfanew);

    auto exportDirRVA = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    auto exportDir = (PIMAGE_EXPORT_DIRECTORY)((DWORD_PTR)dllBase + exportDirRVA);

    auto namesRVA = (DWORD*)((DWORD_PTR)dllBase + exportDir->AddressOfNames);
    auto ordinalsRVA = (WORD*)((DWORD_PTR)dllBase + exportDir->AddressOfNameOrdinals);
    auto functionsRVA = (DWORD*)((DWORD_PTR)dllBase + exportDir->AddressOfFunctions);

    for (DWORD i = 0; i < exportDir->NumberOfNames; i++) {
        const char* name = (const char*)((DWORD_PTR)dllBase + namesRVA[i]);
        if (strcmp(name, functionName) == 0) {
            WORD ordinal = ordinalsRVA[i];
            DWORD functionRVA = functionsRVA[ordinal];
            return (FARPROC)((DWORD_PTR)dllBase + functionRVA);
        }
    }
    return nullptr;
}

PPEB GetPEB() {
    PPEB peb;
    #ifdef _WIN64
        __asm__("mov %%gs:0x60, %0" : "=r" (peb));
    #else
        __asm__("mov %%fs:0x30, %0" : "=r" (peb));
    #endif
    return peb;
}

void* GetKernel32Base() {
    PPEB peb = (PPEB)GetPEB();
    PLIST_ENTRY head = &peb->Ldr->InLoadOrderModuleList;
    PLIST_ENTRY curr = head->Flink;

    while (curr != head) {
        PLDR_DATA_TABLE_ENTRY entry = CONTAINING_RECORD(curr, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
        if (wcsstr(entry->BaseDllName.Buffer, L"KERNEL32.DLL")) {
            return entry->DllBase;
        }
        curr = curr->Flink;
    }
    return NULL;
}

int main() {
    void* kernel32Base = GetKernel32Base();
    std::cout << "KERNEL32.DLL base address: " << std::hex << kernel32Base << std::endl;

    pGetModuleHandleA myGetModuleHandleA = (pGetModuleHandleA)GetFunctionAddress(kernel32Base, "GetModuleHandleA");
    pGetProcAddress myGetProcAddress = (pGetProcAddress)GetFunctionAddress(kernel32Base, "GetProcAddress");

    if (myGetModuleHandleA && myGetProcAddress) {
        std::cout << "GetModuleHandleA: " << std::hex << myGetModuleHandleA << std::endl;
        std::cout << "GetProcAddress: " << std::hex << myGetProcAddress << std::endl;
    } else {
        std::cerr << "Failed to resolve functions." << std::endl;
    }

    std::cout << "Press any key to exit." << std::endl;
    getchar();

    return 0;
}
