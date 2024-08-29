#pragma once

#include "core/payload/IPayload.hpp"
#include "core/payload/defines.hpp"
#include "core/shared/attributes.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include <vector>
#include "data_logo.hpp"

class CPeX86SplashPayload : public IPayload
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

    std::vector<ImportRequirement_t> imports() const
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

    std::vector<SectionData_t> data() const
    {
        return {
            {
                strenc(".data"),
                {
                    { strenc("ClassName db 'BinArmorWindow', 0") },
                    { strenc("WindowName db '', 0") },
                    { strenc("hInstance dd 0") },
                    { strenc("hWnd dd 0") },
                    { strenc("screenSizeX dd 0") },
                    { strenc("screenSizeY dd 0") },
                    { strenc("windowWidth dd 800") },
                    { strenc("windowHeight dd 300") },
                    { dataLogo },
                    { strenc("png_size equ 14161") },
                    { strenc("png_width equ 800") },
                    { strenc("png_height equ 300") },
                    { strenc("png_height equ 300") },
                    { strenc("hIcon dd 0") },
                    { strenc(R"(
                        WndClassEx:
                            dd 0x30
                            dd 0
                            dd WndProc
                            dd 0
                            dd 0
                            dd 0
                            dd 0
                            dd 0
                            dd 6
                            dd 0
                            dd ClassName
                            dd 0
                    )") }
                }
            }
        };
    }

    /*
    * Problem with data relying on some procedures (ref to procedure in data)
    * Problem with data initialization
    * Parsing and replacing the references in asm problem.... :)
    */

    std::vector<SectionProcedures_t> text() const {
        return {
            {
                strenc(".text"),
                {
                    {
                        strenc("exit"),
                        {
                            strenc("call GetLastError"),
                            strenc("push eax"),
                            strenc("call ExitProcess")
                        }
                    },
                    {
                        strenc(".wm_close"),
                        {
                            strenc("push dword [ebp+8]"),
                            strenc("call DestroyWindow"),
                            strenc("xor eax, eax"),
                            strenc("pop ebp"),
                            strenc("ret")
                        },
                    },
                    {
                        strenc(".wm_destroy"),
                        {
                            strenc("push 0"),
                            strenc("call PostQuitMessage"),
                            strenc("xor eax, eax"),
                            strenc("pop ebp"),
                            strenc("ret")
                        }
                    },
                    {
                        strenc(".wm_paint"),
                        {
                            strenc("push dword [ebp+8]"),
                            strenc("call GetDC"),
                            strenc("test eax, eax"),
                            strenc("jz exit"),
                            strenc("push 0x0003"),
                            strenc("push 0"),
                            strenc("push 0"),
                            strenc("push png_height"),
                            strenc("push png_width"),
                            strenc("push dword [hIcon]"),
                            strenc("push 10"),
                            strenc("push 10"),
                            strenc("push eax"),
                            strenc("call DrawIconEx"),
                            strenc("push dword [hIcon]"),
                            strenc("call DestroyIcon"),
                            strenc("mov eax, 1"),
                            strenc("pop ebp"),
                            strenc("ret")
                        }
                    },
                    {
                        strenc("WndProc"),
                        {
                            strenc("push ebp"),
                            strenc("mov ebp, esp"),
                            strenc("mov eax, dword [ebp+12]"),
                            strenc("cmp eax, 0x10"),
                            strenc("je .wm_close"),
                            strenc("cmp eax, 0x2"),
                            strenc("je .wm_destroy"),
                            strenc("cmp eax, 0xF"),
                            strenc("je .wm_paint"),
                            strenc("push dword [ebp+20]"),
                            strenc("push dword [ebp+16]"),
                            strenc("push dword [ebp+12]"),
                            strenc("push dword [ebp+8]"),
                            strenc("call DefWindowProcA"),
                            strenc("pop ebp"),
                            strenc("ret")
                        }
                    },
                    {
                        strenc("showBanner"),
                        {
                            strenc("push ebp"),
                            strenc("mov ebp, esp"),
                            strenc("push 0"),
                            strenc("call GetModuleHandleA"),
                            strenc("mov [hInstance], eax"),
                            strenc("push 0x30000"),
                            strenc("push png_height"),
                            strenc("push png_width"),
                            strenc("push 0x30000"),
                            strenc("push 1"),
                            strenc("push png_size"),
                            strenc("push png_data"),
                            strenc("call CreateIconFromResourceEx"),
                            strenc("test eax, eax"),
                            strenc("jz exit"),
                            strenc("mov [hIcon], eax"),
                            strenc("push WndClassEx"),
                            strenc("call RegisterClassExA"),
                            strenc("test eax, eax"),
                            strenc("jz exit"),
                            strenc("push 0"),
                            strenc("call GetSystemMetrics"),
                            strenc("test eax, eax"),
                            strenc("jz exit"),
                            strenc("mov [screenSizeX], eax"),
                            strenc("push 1"),
                            strenc("call GetSystemMetrics"),
                            strenc("test eax, eax"),
                            strenc("jz exit"),
                            strenc("mov [screenSizeY], eax"),
                            strenc("mov ebx, [screenSizeX]"),
                            strenc("sub ebx, [windowWidth]"),
                            strenc("shr ebx, 1"),
                            strenc("mov ecx, [screenSizeY]"),
                            strenc("sub ecx, [windowHeight]"),
                            strenc("shr ecx, 1"),
                            strenc("xor edx, edx"),
                            strenc("or edx, 0x08000000"),
                            strenc("push 0"),
                            strenc("push dword [hInstance]"),
                            strenc("push 0"),
                            strenc("push 0"),
                            strenc("push dword [windowHeight]"),
                            strenc("push dword [windowWidth]"),
                            strenc("push ecx"),
                            strenc("push ebx"),
                            strenc("push 0x80000000"),
                            strenc("push WindowName"),
                            strenc("push ClassName"),
                            strenc("push edx"),
                            strenc("call CreateWindowExA"),
                            strenc("mov [hWnd], eax"),
                            strenc("test eax, eax"),
                            strenc("jz exit"),
                            strenc("push 1"),
                            strenc("push dword [hWnd]"),
                            strenc("call ShowWindow"),
                            strenc("push dword [hWnd]"),
                            strenc("call UpdateWindow"),
                            strenc("push 3000"),
                            strenc("call Sleep"),
                            strenc("push dword [hWnd]"),
                            strenc("call DestroyWindow"),
                            strenc("pop ebp"),
                            strenc("ret")
                        }
                    }
                }
            }
        };
    }
};
