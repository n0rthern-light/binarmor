#ifndef SHARED_SELF_OBFUSCATION_WIN_API_HPP_
#define SHARED_SELF_OBFUSCATION_WIN_API_HPP_

#include <Windows.h>
#include <psapi.h>
#include "strenc.hpp"

// libraries
#define KERNEL32 strenc("kernel32.dll")

// functions
#define KERNEL32_GetModuleHandleA strenc("GetModuleHandleA")
#define KERNEL32_GetProcAddress strenc("GetProcAddress")
#define KERNEL32_LoadLibraryA strenc("LoadLibraryA")
#define KERNEL32_GetModuleInformation strenc("K32GetModuleInformation")
#define KERNEL32_GetCurrentProcess strenc("GetCurrentProcess")

// kernel32
typedef HMODULE(WINAPI* pGetModuleHandleA)(LPCSTR);
typedef FARPROC(WINAPI* pGetProcAddress)(HMODULE, LPCSTR);
typedef HMODULE(WINAPI* pLoadLibraryA)(LPCSTR);
typedef MODULEINFO(WINAPI* pGetModuleInformation)(HANDLE, HMODULE, LPMODULEINFO, DWORD);
typedef HANDLE(WINAPI* pGetCurrentProcess)();
typedef BOOLEAN(WINAPI* pIsDebuggerPresent)();
typedef DWORD(WINAPI* pGetModuleFileNameA)(HMODULE, LPSTR, DWORD);

// ntdll
typedef NTSTATUS(WINAPI* pNtQuerySystemTime)(PLARGE_INTEGER SystemTime);

#endif // SHARED_SELF_OBFUSCATION_WIN_API_HPP_
