#ifndef LINKING_H
#define LINKING_H

#include "no_strings.hpp"

#define KERNEL32 strenc("kernel32.dll")
#define KERNEL32_GetModuleHandleA strenc("GetModuleHandleA")
#define KERNEL32_GetProcAddress strenc("GetProcAddress")
#define KERNEL32_LoadLibraryA strenc("LoadLibraryA")

#endif