#ifndef LINKING_H
#define LINKING_H

#include <Windows.h>
#include "strenc.hpp"

#define KERNEL32 strenc("kernel32.dll")
#define KERNEL32_GetModuleHandleA strenc("GetModuleHandleA")
#define KERNEL32_GetProcAddress strenc("GetProcAddress")
#define KERNEL32_LoadLibraryA strenc("LoadLibraryA")

typedef HMODULE(WINAPI* pGetModuleHandleA)(LPCSTR);
typedef FARPROC(WINAPI* pGetProcAddress)(HMODULE, LPCSTR);
typedef HMODULE(WINAPI *pLoadLibraryA)(LPCSTR);

#endif