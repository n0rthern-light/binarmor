#pragma once

#include "core/assembler/defines.hpp"
#include "core/payload/IPayload.hpp"
#include "core/payload/defines.hpp"
#include "core/shared/attributes.hpp"
#include "shared/RuntimeException.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include <vector>
#include <format>

class PeX86SplashPayload : public IPayload
{
    std::string id() const
    {
        return "splash_main";
    }

    Architecture architecture() const
    {
        return Architecture::X86;
    }

    Format format() const
    {
        return Format::Windows_PE;
    }

    std::vector<ImportRequirement_t> requiredImports() const
    {
        return {
            { strenc("KERNEL32.dll"), strenc("GetModuleHandleA") },
            { strenc("KERNEL32.dll"), strenc("GetLastError") },
            { strenc("KERNEL32.dll"), strenc("Sleep") },
            { strenc("KERNEL32.dll"), strenc("ExitProcess") },

            { strenc("USER32.dll"), strenc("CreateIconFromResourceEx") },
            { strenc("USER32.dll"), strenc("GetDC") },
            { strenc("USER32.dll"), strenc("DrawIconEx") },
            { strenc("USER32.dll"), strenc("DestroyIcon") },
            { strenc("USER32.dll"), strenc("RegisterClassExA") },
            { strenc("USER32.dll"), strenc("GetSystemMetrics") },
            { strenc("USER32.dll"), strenc("CreateWindowExA") },
            { strenc("USER32.dll"), strenc("ShowWindow") },
            { strenc("USER32.dll"), strenc("UpdateWindow") },
            { strenc("USER32.dll"), strenc("DestroyWindow") },
            { strenc("USER32.dll"), strenc("PostQuitMessage") },
            { strenc("USER32.dll"), strenc("DefWindowProcA") },
        };
    }

    std::vector<DataRequirement_t> requiredData() const
    {
        return {
            { strenc("ClassName") },
            { strenc("WindowName") },
            { strenc("hInstance") },
            { strenc("hWnd") },
            { strenc("screenSizeX") },
            { strenc("screenSizeY") },
            { strenc("windowWidth") },
            { strenc("windowHeight") },
            { strenc("pngData") },
            { strenc("pngSize"), DataResolveType::VALUE, 2 },
            { strenc("pngWidth"), DataResolveType::VALUE, 2 },
            { strenc("pngHeight"), DataResolveType::VALUE, 2 },
            { strenc("hIcon") },
            { strenc("WndClassEx") },
        };
    }

    std::vector<Procedure_t> content() const {
        return {
            {
                "exit",
                {
                    "call GetLastError",
                    "push eax",
                    "call ExitProcess"
                }
            },
            {
                ".wm_close",
                {
                    "push dword [ebp+8]",
                    "call DestroyWindow",
                    "xor eax, eax",
                    "pop ebp",
                    "ret"
                },
            },
            {
                ".wm_destroy",
                {
                    "push 0",
                    "call PostQuitMessage",
                    "xor eax, eax",
                    "pop ebp",
                    "ret"
                }
            },
            {
                ".wm_paint",
                {
                    "push dword [ebp+8]",
                    "call GetDC",
                    "test eax, eax",
                    "jz exit",
                    "push 0x0003",
                    "push 0",
                    "push 0",
                    "push png_height ",
                    "push png_width ",
                    "push dword [hIcon]",
                    "push 10",
                    "push 10",
                    "push eax",
                    "call DrawIconEx",
                    "push dword [hIcon]",
                    "call DestroyIcon",
                    "mov eax, 1",
                    "pop ebp",
                    "ret"
                }
            },
            {
                "WndProc",
                {
                    "push ebp",
                    "mov ebp, esp",
                    "mov eax, dword [ebp+12]",
                    "cmp eax, 0x10",
                    "je .wm_close",
                    "cmp eax, 0x2",
                    "je .wm_destroy",
                    "cmp eax, 0xF",
                    "je .wm_paint",
                    "push dword [ebp+20]",
                    "push dword [ebp+16]",
                    "push dword [ebp+12]",
                    "push dword [ebp+8]",
                    "call DefWindowProcA",
                    "pop ebp",
                    "ret"
                }
            },
            {
                "showBanner",
                {
                    "push ebp",
                    "mov ebp, esp",
                    "push 0",
                    "call GetModuleHandleA",
                    "mov [hInstance], eax",
                    "push 0x30000",
                    "push png_height",
                    "push png_width",
                    "push 0x30000",
                    "push 1",
                    "push png_size",
                    "push png_data",
                    "call CreateIconFromResourceEx",
                    "test eax, eax",
                    "jz exit",
                    "mov [hIcon], eax",
                    "push WndClassEx",
                    "call RegisterClassExA",
                    "test eax, eax",
                    "jz exit",
                    "push 0",
                    "call GetSystemMetrics",
                    "test eax, eax",
                    "jz exit",
                    "mov [screenSizeX], eax",
                    "push 1",
                    "call GetSystemMetrics",
                    "test eax, eax",
                    "jz exit",
                    "mov [screenSizeY], eax",
                    "mov ebx, [screenSizeX]",
                    "sub ebx, [windowWidth]",
                    "shr ebx, 1",
                    "mov ecx, [screenSizeY]",
                    "sub ecx, [windowHeight]",
                    "shr ecx, 1",
                    "xor edx, edx",
                    "or edx, 0x08000000",
                    "push 0",
                    "push dword [hInstance]",
                    "push 0",
                    "push 0",
                    "push dword [windowHeight]",
                    "push dword [windowWidth]",
                    "push ecx",
                    "push ebx",
                    "push 0x80000000",
                    "push WindowName",
                    "push ClassName",
                    "push edx",
                    "call CreateWindowExA",
                    "mov [hWnd], eax",
                    "test eax, eax",
                    "jz exit",
                    "push 1",
                    "push dword [hWnd]",
                    "call ShowWindow",
                    "push dword [hWnd]",
                    "call UpdateWindow",
                    "push 3000",
                    "call Sleep",
                    "push dword [hWnd]",
                    "call DestroyWindow",
                    "pop ebp",
                    "ret",
                }
            }
        };
    }
};
