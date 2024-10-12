#include <gtest/gtest.h>
#include "../../BinaryMother.hpp"
#include <stdio.h>

TEST(PeImportTest, X86ExeImportsAreCorrect)
{
    auto pe = BinaryMother::x86exe();
    auto imports = pe->peImportModules();
    ASSERT_EQ(imports.size(), 2);

    {
        SCOPED_TRACE("KERNEL32");

        auto kernel32 = imports.find("KERNEL32.dll");
        ASSERT_NE(kernel32, imports.end());

        auto kernel32Module = kernel32->second;

        ASSERT_STREQ(kernel32Module->name().c_str(), "KERNEL32.dll");
        ASSERT_EQ(kernel32Module->rvaImportDescriptor(), 0xC000);
        ASSERT_EQ(kernel32Module->sizeOfImportDescriptor(), 0x14);
        ASSERT_EQ(pe->rvaToOffset(kernel32Module->rvaImportDescriptor()), 0x8A00);

        pe_import_vec kernel32ModuleImports = kernel32Module->peImports();
        ASSERT_EQ(kernel32ModuleImports.size(), 15);

        {
            SCOPED_TRACE("Imported functions");

            ASSERT_STREQ(kernel32ModuleImports[0]->name().c_str(), "DeleteCriticalSection");
            ASSERT_EQ(kernel32ModuleImports[0]->hint(), 0x113);
            ASSERT_EQ(kernel32ModuleImports[0]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaOriginalThunk(), 0xC03C);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaThunk(), 0xC10C);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaOriginalThunkAddressOfData(), 0xC1DC);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaThunkAddressOfData(), 0xC1DC);
            ASSERT_EQ(kernel32ModuleImports[0]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[0]->rvaOriginalThunk()), 0x8A3C);

            ASSERT_STREQ(kernel32ModuleImports[1]->name().c_str(), "EnterCriticalSection");
            ASSERT_EQ(kernel32ModuleImports[1]->hint(), 0x134);
            ASSERT_EQ(kernel32ModuleImports[1]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaOriginalThunk(), 0xC040);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaThunk(), 0xC110);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaOriginalThunkAddressOfData(), 0xC1F4);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaThunkAddressOfData(), 0xC1F4);
            ASSERT_EQ(kernel32ModuleImports[1]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[1]->rvaOriginalThunk()), 0x8A40);

            ASSERT_STREQ(kernel32ModuleImports[13]->name().c_str(), "VirtualQuery");
            ASSERT_EQ(kernel32ModuleImports[13]->hint(), 0x5BC);
            ASSERT_EQ(kernel32ModuleImports[13]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[13]->rvaOriginalThunk(), 0xC070);
            ASSERT_EQ(kernel32ModuleImports[13]->rvaThunk(), 0xC140);
            ASSERT_EQ(kernel32ModuleImports[13]->rvaOriginalThunkAddressOfData(), 0xC2E6);
            ASSERT_EQ(kernel32ModuleImports[13]->rvaThunkAddressOfData(), 0xC2E6);
            ASSERT_EQ(kernel32ModuleImports[13]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[13]->rvaOriginalThunk()), 0x8A70);

            ASSERT_STREQ(kernel32ModuleImports[14]->name().c_str(), "WideCharToMultiByte");
            ASSERT_EQ(kernel32ModuleImports[14]->hint(), 0x5EE);
            ASSERT_EQ(kernel32ModuleImports[14]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[14]->rvaOriginalThunk(), 0xC074);
            ASSERT_EQ(kernel32ModuleImports[14]->rvaThunk(), 0xC144);
            ASSERT_EQ(kernel32ModuleImports[14]->rvaOriginalThunkAddressOfData(), 0xC2F6);
            ASSERT_EQ(kernel32ModuleImports[14]->rvaThunkAddressOfData(), 0xC2F6);
            ASSERT_EQ(kernel32ModuleImports[14]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[14]->rvaOriginalThunk()), 0x8A74);
        }
    }

    {
        SCOPED_TRACE("msvcrt.dll");

        auto msvcrt = imports.find("msvcrt.dll");
        ASSERT_NE(msvcrt, imports.end());

        auto msvcrtModule = msvcrt->second;

        ASSERT_STREQ(msvcrtModule->name().c_str(), "msvcrt.dll");
        ASSERT_EQ(msvcrtModule->rvaImportDescriptor(), 0xC014);
        ASSERT_EQ(msvcrtModule->sizeOfImportDescriptor(), 0x14);
        ASSERT_EQ(pe->rvaToOffset(msvcrtModule->rvaImportDescriptor()), 0x8A14);

        auto msvcrtModuleImports = msvcrtModule->peImports();
        ASSERT_EQ(msvcrtModuleImports.size(), 35);

        {
            SCOPED_TRACE("Imported functions");

            ASSERT_STREQ(msvcrtModuleImports[0]->name().c_str(), "__getmainargs");
            ASSERT_EQ(msvcrtModuleImports[0]->hint(), 0x3A);
            ASSERT_EQ(msvcrtModuleImports[0]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaOriginalThunk(), 0xC07C);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaThunk(), 0xC14C);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaOriginalThunkAddressOfData(), 0xC30C);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaThunkAddressOfData(), 0xC30C);
            ASSERT_EQ(msvcrtModuleImports[0]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[0]->rvaOriginalThunk()), 0x8A7C);

            ASSERT_STREQ(msvcrtModuleImports[1]->name().c_str(), "__initenv");
            ASSERT_EQ(msvcrtModuleImports[1]->hint(), 0x3B);
            ASSERT_EQ(msvcrtModuleImports[1]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaOriginalThunk(), 0xC080);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaThunk(), 0xC150);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaOriginalThunkAddressOfData(), 0xC31C);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaThunkAddressOfData(), 0xC31C);
            ASSERT_EQ(msvcrtModuleImports[1]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[1]->rvaOriginalThunk()), 0x8A80);

            ASSERT_STREQ(msvcrtModuleImports[33]->name().c_str(), "vfprintf");
            ASSERT_EQ(msvcrtModuleImports[33]->hint(), 0x502);
            ASSERT_EQ(msvcrtModuleImports[33]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[33]->rvaOriginalThunk(), 0xC100);
            ASSERT_EQ(msvcrtModuleImports[33]->rvaThunk(), 0xC1D0);
            ASSERT_EQ(msvcrtModuleImports[33]->rvaOriginalThunkAddressOfData(), 0xC480);
            ASSERT_EQ(msvcrtModuleImports[33]->rvaThunkAddressOfData(), 0xC480);
            ASSERT_EQ(msvcrtModuleImports[33]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[33]->rvaOriginalThunk()), 0x8B00);

            ASSERT_STREQ(msvcrtModuleImports[34]->name().c_str(), "wcslen");
            ASSERT_EQ(msvcrtModuleImports[34]->hint(), 0x51C);
            ASSERT_EQ(msvcrtModuleImports[34]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[34]->rvaOriginalThunk(), 0xC104);
            ASSERT_EQ(msvcrtModuleImports[34]->rvaThunk(), 0xC1D4);
            ASSERT_EQ(msvcrtModuleImports[34]->rvaOriginalThunkAddressOfData(), 0xC48C);
            ASSERT_EQ(msvcrtModuleImports[34]->rvaThunkAddressOfData(), 0xC48C);
            ASSERT_EQ(msvcrtModuleImports[34]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[34]->rvaOriginalThunk()), 0x8B04);
        }
    }
}

TEST(PeImportTest, X86DllImportsAreCorrect)
{
    auto pe = BinaryMother::x86dll();
    auto imports = pe->peImportModules();
    ASSERT_EQ(imports.size(), 2);

    {
        SCOPED_TRACE("KERNEL32");

        auto kernel32 = imports.find("KERNEL32.dll");
        ASSERT_NE(kernel32, imports.end());

        auto kernel32Module = kernel32->second;

        ASSERT_STREQ(kernel32Module->name().c_str(), "KERNEL32.dll");
        ASSERT_EQ(kernel32Module->rvaImportDescriptor(), 0xD000);
        ASSERT_EQ(kernel32Module->sizeOfImportDescriptor(), 0x14);
        ASSERT_EQ(pe->rvaToOffset(kernel32Module->rvaImportDescriptor()), 0x8800);

        pe_import_vec kernel32ModuleImports = kernel32Module->peImports();
        ASSERT_EQ(kernel32ModuleImports.size(), 14);

        {
            SCOPED_TRACE("Imported functions");

            ASSERT_STREQ(kernel32ModuleImports[0]->name().c_str(), "DeleteCriticalSection");
            ASSERT_EQ(kernel32ModuleImports[0]->hint(), 0x113);
            ASSERT_EQ(kernel32ModuleImports[0]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaOriginalThunk(), 0xD03C);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaThunk(), 0xD0E0);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaOriginalThunkAddressOfData(), 0xD184);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaThunkAddressOfData(), 0xD184);
            ASSERT_EQ(kernel32ModuleImports[0]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[0]->rvaOriginalThunk()), 0x883C);

            ASSERT_STREQ(kernel32ModuleImports[1]->name().c_str(), "EnterCriticalSection");
            ASSERT_EQ(kernel32ModuleImports[1]->hint(), 0x134);
            ASSERT_EQ(kernel32ModuleImports[1]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaOriginalThunk(), 0xD040);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaThunk(), 0xD0E4);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaOriginalThunkAddressOfData(), 0xD19C);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaThunkAddressOfData(), 0xD19C);
            ASSERT_EQ(kernel32ModuleImports[1]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[1]->rvaOriginalThunk()), 0x8840);

            ASSERT_STREQ(kernel32ModuleImports[12]->name().c_str(), "VirtualQuery");
            ASSERT_EQ(kernel32ModuleImports[12]->hint(), 0x5BC);
            ASSERT_EQ(kernel32ModuleImports[12]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[12]->rvaOriginalThunk(), 0xD06C);
            ASSERT_EQ(kernel32ModuleImports[12]->rvaThunk(), 0xD110);
            ASSERT_EQ(kernel32ModuleImports[12]->rvaOriginalThunkAddressOfData(), 0xD270);
            ASSERT_EQ(kernel32ModuleImports[12]->rvaThunkAddressOfData(), 0xD270);
            ASSERT_EQ(kernel32ModuleImports[12]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[12]->rvaOriginalThunk()), 0x886C);

            ASSERT_STREQ(kernel32ModuleImports[13]->name().c_str(), "WideCharToMultiByte");
            ASSERT_EQ(kernel32ModuleImports[13]->hint(), 0x5EE);
            ASSERT_EQ(kernel32ModuleImports[13]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[13]->rvaOriginalThunk(), 0xD070);
            ASSERT_EQ(kernel32ModuleImports[13]->rvaThunk(), 0xD114);
            ASSERT_EQ(kernel32ModuleImports[13]->rvaOriginalThunkAddressOfData(), 0xD280);
            ASSERT_EQ(kernel32ModuleImports[13]->rvaThunkAddressOfData(), 0xD280);
            ASSERT_EQ(kernel32ModuleImports[13]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[13]->rvaOriginalThunk()), 0x8870);
        }
    }

    {
        SCOPED_TRACE("msvcrt.dll");

        auto msvcrt = imports.find("msvcrt.dll");
        ASSERT_NE(msvcrt, imports.end());

        auto msvcrtModule = msvcrt->second;

        ASSERT_STREQ(msvcrtModule->name().c_str(), "msvcrt.dll");
        ASSERT_EQ(msvcrtModule->rvaImportDescriptor(), 0xD014);
        ASSERT_EQ(msvcrtModule->sizeOfImportDescriptor(), 0x14);
        ASSERT_EQ(pe->rvaToOffset(msvcrtModule->rvaImportDescriptor()), 0x8814);

        auto msvcrtModuleImports = msvcrtModule->peImports();
        ASSERT_EQ(msvcrtModuleImports.size(), 25);

        {
            SCOPED_TRACE("Imported functions");

            ASSERT_STREQ(msvcrtModuleImports[0]->name().c_str(), "__mb_cur_max");
            ASSERT_EQ(msvcrtModuleImports[0]->hint(), 0x48);
            ASSERT_EQ(msvcrtModuleImports[0]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaOriginalThunk(), 0xD078);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaThunk(), 0xD11C);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaOriginalThunkAddressOfData(), 0xD296);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaThunkAddressOfData(), 0xD296);
            ASSERT_EQ(msvcrtModuleImports[0]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[0]->rvaOriginalThunk()), 0x8878);

            ASSERT_STREQ(msvcrtModuleImports[1]->name().c_str(), "_amsg_exit");
            ASSERT_EQ(msvcrtModuleImports[1]->hint(), 0x93);
            ASSERT_EQ(msvcrtModuleImports[1]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaOriginalThunk(), 0xD07C);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaThunk(), 0xD120);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaOriginalThunkAddressOfData(), 0xD2A6);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaThunkAddressOfData(), 0xD2A6);
            ASSERT_EQ(msvcrtModuleImports[1]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[1]->rvaOriginalThunk()), 0x887C);

            ASSERT_STREQ(msvcrtModuleImports[23]->name().c_str(), "vfprintf");
            ASSERT_EQ(msvcrtModuleImports[23]->hint(), 0x502);
            ASSERT_EQ(msvcrtModuleImports[23]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[23]->rvaOriginalThunk(), 0xD0D4);
            ASSERT_EQ(msvcrtModuleImports[23]->rvaThunk(), 0xD178);
            ASSERT_EQ(msvcrtModuleImports[23]->rvaOriginalThunkAddressOfData(), 0xD384);
            ASSERT_EQ(msvcrtModuleImports[23]->rvaThunkAddressOfData(), 0xD384);
            ASSERT_EQ(msvcrtModuleImports[23]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[23]->rvaOriginalThunk()), 0x88D4);

            ASSERT_STREQ(msvcrtModuleImports[24]->name().c_str(), "wcslen");
            ASSERT_EQ(msvcrtModuleImports[24]->hint(), 0x51C);
            ASSERT_EQ(msvcrtModuleImports[24]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[24]->rvaOriginalThunk(), 0xD0D8);
            ASSERT_EQ(msvcrtModuleImports[24]->rvaThunk(), 0xD17C);
            ASSERT_EQ(msvcrtModuleImports[24]->rvaOriginalThunkAddressOfData(), 0xD390);
            ASSERT_EQ(msvcrtModuleImports[24]->rvaThunkAddressOfData(), 0xD390);
            ASSERT_EQ(msvcrtModuleImports[24]->sizeOfThunk(), 0x4);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[24]->rvaOriginalThunk()), 0x88D8);
        }
    }
}

TEST(PeImportTest, X86_64ExeImportsAreCorrect)
{
    auto pe = BinaryMother::x86_64exe();
    auto imports = pe->peImportModules();

    ASSERT_EQ(imports.size(), 2);

    {
        SCOPED_TRACE("KERNEL32");

        auto kernel32 = imports.find("KERNEL32.dll");
        ASSERT_NE(kernel32, imports.end());

        auto kernel32Module = kernel32->second;

        ASSERT_STREQ(kernel32Module->name().c_str(), "KERNEL32.dll");
        ASSERT_EQ(kernel32Module->rvaImportDescriptor(), 0xE000);
        ASSERT_EQ(kernel32Module->sizeOfImportDescriptor(), 0x14);
        ASSERT_EQ(pe->rvaToOffset(kernel32Module->rvaImportDescriptor()), 0x9400);

        pe_import_vec kernel32ModuleImports = kernel32Module->peImports();
        ASSERT_EQ(kernel32ModuleImports.size(), 13);

        {
            SCOPED_TRACE("Imported functions");

            ASSERT_STREQ(kernel32ModuleImports[0]->name().c_str(), "DeleteCriticalSection");
            ASSERT_EQ(kernel32ModuleImports[0]->hint(), 0x119);
            ASSERT_EQ(kernel32ModuleImports[0]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaOriginalThunk(), 0xE040);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaThunk(), 0xE1C8);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaOriginalThunkAddressOfData(), 0xE350);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaThunkAddressOfData(), 0xE350);
            ASSERT_EQ(kernel32ModuleImports[0]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[0]->rvaOriginalThunk()), 0x9440);

            ASSERT_STREQ(kernel32ModuleImports[1]->name().c_str(), "EnterCriticalSection");
            ASSERT_EQ(kernel32ModuleImports[1]->hint(), 0x13D);
            ASSERT_EQ(kernel32ModuleImports[1]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaOriginalThunk(), 0xE048);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaThunk(), 0xE1D0);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaOriginalThunkAddressOfData(), 0xE368);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaThunkAddressOfData(), 0xE368);
            ASSERT_EQ(kernel32ModuleImports[1]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[1]->rvaOriginalThunk()), 0x9448);

            ASSERT_STREQ(kernel32ModuleImports[11]->name().c_str(), "VirtualQuery");
            ASSERT_EQ(kernel32ModuleImports[11]->hint(), 0x5D3);
            ASSERT_EQ(kernel32ModuleImports[11]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[11]->rvaOriginalThunk(), 0xE098);
            ASSERT_EQ(kernel32ModuleImports[11]->rvaThunk(), 0xE220);
            ASSERT_EQ(kernel32ModuleImports[11]->rvaOriginalThunkAddressOfData(), 0xE434);
            ASSERT_EQ(kernel32ModuleImports[11]->rvaThunkAddressOfData(), 0xE434);
            ASSERT_EQ(kernel32ModuleImports[11]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[11]->rvaOriginalThunk()), 0x9498);

            ASSERT_STREQ(kernel32ModuleImports[12]->name().c_str(), "WideCharToMultiByte");
            ASSERT_EQ(kernel32ModuleImports[12]->hint(), 0x608);
            ASSERT_EQ(kernel32ModuleImports[12]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[12]->rvaOriginalThunk(), 0xE0A0);
            ASSERT_EQ(kernel32ModuleImports[12]->rvaThunk(), 0xE228);
            ASSERT_EQ(kernel32ModuleImports[12]->rvaOriginalThunkAddressOfData(), 0xE444);
            ASSERT_EQ(kernel32ModuleImports[12]->rvaThunkAddressOfData(), 0xE444);
            ASSERT_EQ(kernel32ModuleImports[12]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[12]->rvaOriginalThunk()), 0x94A0);
        }
    }

    {
        SCOPED_TRACE("msvcrt.dll");

        auto msvcrt = imports.find("msvcrt.dll");
        ASSERT_NE(msvcrt, imports.end());

        auto msvcrtModule = msvcrt->second;

        ASSERT_STREQ(msvcrtModule->name().c_str(), "msvcrt.dll");
        ASSERT_EQ(msvcrtModule->rvaImportDescriptor(), 0xE014);
        ASSERT_EQ(msvcrtModule->sizeOfImportDescriptor(), 0x14);
        ASSERT_EQ(pe->rvaToOffset(msvcrtModule->rvaImportDescriptor()), 0x9414);

        auto msvcrtModuleImports = msvcrtModule->peImports();
        ASSERT_EQ(msvcrtModuleImports.size(), 34);

        {
            SCOPED_TRACE("Imported functions");

            ASSERT_STREQ(msvcrtModuleImports[0]->name().c_str(), "__C_specific_handler");
            ASSERT_EQ(msvcrtModuleImports[0]->hint(), 0x38);
            ASSERT_EQ(msvcrtModuleImports[0]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaOriginalThunk(), 0xE0B0);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaThunk(), 0xE238);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaOriginalThunkAddressOfData(), 0xE45A);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaThunkAddressOfData(), 0xE45A);
            ASSERT_EQ(msvcrtModuleImports[0]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[0]->rvaOriginalThunk()), 0x94B0);

            ASSERT_STREQ(msvcrtModuleImports[1]->name().c_str(), "___lc_codepage_func");
            ASSERT_EQ(msvcrtModuleImports[1]->hint(), 0x40);
            ASSERT_EQ(msvcrtModuleImports[1]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaOriginalThunk(), 0xE0B8);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaThunk(), 0xE240);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaOriginalThunkAddressOfData(), 0xE472);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaThunkAddressOfData(), 0xE472);
            ASSERT_EQ(msvcrtModuleImports[1]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[1]->rvaOriginalThunk()), 0x94B8);

            ASSERT_STREQ(msvcrtModuleImports[32]->name().c_str(), "vfprintf");
            ASSERT_EQ(msvcrtModuleImports[32]->hint(), 0x4FD);
            ASSERT_EQ(msvcrtModuleImports[32]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[32]->rvaOriginalThunk(), 0xE1B0);
            ASSERT_EQ(msvcrtModuleImports[32]->rvaThunk(), 0xE338);
            ASSERT_EQ(msvcrtModuleImports[32]->rvaOriginalThunkAddressOfData(), 0xE5E2);
            ASSERT_EQ(msvcrtModuleImports[32]->rvaThunkAddressOfData(), 0xE5E2);
            ASSERT_EQ(msvcrtModuleImports[32]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[32]->rvaOriginalThunk()), 0x95B0);

            ASSERT_STREQ(msvcrtModuleImports[33]->name().c_str(), "wcslen");
            ASSERT_EQ(msvcrtModuleImports[33]->hint(), 0x516);
            ASSERT_EQ(msvcrtModuleImports[33]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[33]->rvaOriginalThunk(), 0xE1B8);
            ASSERT_EQ(msvcrtModuleImports[33]->rvaThunk(), 0xE340);
            ASSERT_EQ(msvcrtModuleImports[33]->rvaOriginalThunkAddressOfData(), 0xE5EE);
            ASSERT_EQ(msvcrtModuleImports[33]->rvaThunkAddressOfData(), 0xE5EE);
            ASSERT_EQ(msvcrtModuleImports[33]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[33]->rvaOriginalThunk()), 0x95B8);
        }
    }
}

TEST(PeImportTest, X86_64DllImportsAreCorrect)
{
    auto pe = BinaryMother::x86_64dll();
    auto imports = pe->peImportModules();

    ASSERT_EQ(imports.size(), 2);

    {
        SCOPED_TRACE("KERNEL32");

        auto kernel32 = imports.find("KERNEL32.dll");
        ASSERT_NE(kernel32, imports.end());

        auto kernel32Module = kernel32->second;

        ASSERT_STREQ(kernel32Module->name().c_str(), "KERNEL32.dll");
        ASSERT_EQ(kernel32Module->rvaImportDescriptor(), 0xE000);
        ASSERT_EQ(kernel32Module->sizeOfImportDescriptor(), 0x14);
        ASSERT_EQ(pe->rvaToOffset(kernel32Module->rvaImportDescriptor()), 0x9000);

        pe_import_vec kernel32ModuleImports = kernel32Module->peImports();
        ASSERT_EQ(kernel32ModuleImports.size(), 12);

        {
            SCOPED_TRACE("Imported functions");

            ASSERT_STREQ(kernel32ModuleImports[0]->name().c_str(), "DeleteCriticalSection");
            ASSERT_EQ(kernel32ModuleImports[0]->hint(), 0x119);
            ASSERT_EQ(kernel32ModuleImports[0]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaOriginalThunk(), 0xE040);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaThunk(), 0xE168);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaOriginalThunkAddressOfData(), 0xE290);
            ASSERT_EQ(kernel32ModuleImports[0]->rvaThunkAddressOfData(), 0xE290);
            ASSERT_EQ(kernel32ModuleImports[0]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[0]->rvaOriginalThunk()), 0x9040);

            ASSERT_STREQ(kernel32ModuleImports[1]->name().c_str(), "EnterCriticalSection");
            ASSERT_EQ(kernel32ModuleImports[1]->hint(), 0x13D);
            ASSERT_EQ(kernel32ModuleImports[1]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaOriginalThunk(), 0xE048);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaThunk(), 0xE170);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaOriginalThunkAddressOfData(), 0xE2A8);
            ASSERT_EQ(kernel32ModuleImports[1]->rvaThunkAddressOfData(), 0xE2A8);
            ASSERT_EQ(kernel32ModuleImports[1]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[1]->rvaOriginalThunk()), 0x9048);

            ASSERT_STREQ(kernel32ModuleImports[10]->name().c_str(), "VirtualQuery");
            ASSERT_EQ(kernel32ModuleImports[10]->hint(), 0x5D3);
            ASSERT_EQ(kernel32ModuleImports[10]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[10]->rvaOriginalThunk(), 0xE090);
            ASSERT_EQ(kernel32ModuleImports[10]->rvaThunk(), 0xE1B8);
            ASSERT_EQ(kernel32ModuleImports[10]->rvaOriginalThunkAddressOfData(), 0xE356);
            ASSERT_EQ(kernel32ModuleImports[10]->rvaThunkAddressOfData(), 0xE356);
            ASSERT_EQ(kernel32ModuleImports[10]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[10]->rvaOriginalThunk()), 0x9090);

            ASSERT_STREQ(kernel32ModuleImports[11]->name().c_str(), "WideCharToMultiByte");
            ASSERT_EQ(kernel32ModuleImports[11]->hint(), 0x608);
            ASSERT_EQ(kernel32ModuleImports[11]->ordinal(), 0);
            ASSERT_EQ(kernel32ModuleImports[11]->rvaOriginalThunk(), 0xE098);
            ASSERT_EQ(kernel32ModuleImports[11]->rvaThunk(), 0xE1C0);
            ASSERT_EQ(kernel32ModuleImports[11]->rvaOriginalThunkAddressOfData(), 0xE366);
            ASSERT_EQ(kernel32ModuleImports[11]->rvaThunkAddressOfData(), 0xE366);
            ASSERT_EQ(kernel32ModuleImports[11]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(kernel32ModuleImports[11]->rvaOriginalThunk()), 0x9098);
        }
    }

    {
        SCOPED_TRACE("msvcrt.dll");

        auto msvcrt = imports.find("msvcrt.dll");
        ASSERT_NE(msvcrt, imports.end());

        auto msvcrtModule = msvcrt->second;

        ASSERT_STREQ(msvcrtModule->name().c_str(), "msvcrt.dll");
        ASSERT_EQ(msvcrtModule->rvaImportDescriptor(), 0xE014);
        ASSERT_EQ(msvcrtModule->sizeOfImportDescriptor(), 0x14);
        ASSERT_EQ(pe->rvaToOffset(msvcrtModule->rvaImportDescriptor()), 0x9014);

        auto msvcrtModuleImports = msvcrtModule->peImports();
        ASSERT_EQ(msvcrtModuleImports.size(), 23);

        {
            SCOPED_TRACE("Imported functions");

            ASSERT_STREQ(msvcrtModuleImports[0]->name().c_str(), "___lc_codepage_func");
            ASSERT_EQ(msvcrtModuleImports[0]->hint(), 0x40);
            ASSERT_EQ(msvcrtModuleImports[0]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaOriginalThunk(), 0xE0A8);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaThunk(), 0xE1D0);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaOriginalThunkAddressOfData(), 0xE37C);
            ASSERT_EQ(msvcrtModuleImports[0]->rvaThunkAddressOfData(), 0xE37C);
            ASSERT_EQ(msvcrtModuleImports[0]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[0]->rvaOriginalThunk()), 0x90A8);

            ASSERT_STREQ(msvcrtModuleImports[1]->name().c_str(), "___mb_cur_max_func");
            ASSERT_EQ(msvcrtModuleImports[1]->hint(), 0x43);
            ASSERT_EQ(msvcrtModuleImports[1]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaOriginalThunk(), 0xE0B0);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaThunk(), 0xE1D8);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaOriginalThunkAddressOfData(), 0xE392);
            ASSERT_EQ(msvcrtModuleImports[1]->rvaThunkAddressOfData(), 0xE392);
            ASSERT_EQ(msvcrtModuleImports[1]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[1]->rvaOriginalThunk()), 0x90B0);

            ASSERT_STREQ(msvcrtModuleImports[21]->name().c_str(), "vfprintf");
            ASSERT_EQ(msvcrtModuleImports[21]->hint(), 0x4FD);
            ASSERT_EQ(msvcrtModuleImports[21]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[21]->rvaOriginalThunk(), 0xE150);
            ASSERT_EQ(msvcrtModuleImports[21]->rvaThunk(), 0xE278);
            ASSERT_EQ(msvcrtModuleImports[21]->rvaOriginalThunkAddressOfData(), 0xE46E);
            ASSERT_EQ(msvcrtModuleImports[21]->rvaThunkAddressOfData(), 0xE46E);
            ASSERT_EQ(msvcrtModuleImports[21]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[21]->rvaOriginalThunk()), 0x9150);

            ASSERT_STREQ(msvcrtModuleImports[22]->name().c_str(), "wcslen");
            ASSERT_EQ(msvcrtModuleImports[22]->hint(), 0x516);
            ASSERT_EQ(msvcrtModuleImports[22]->ordinal(), 0);
            ASSERT_EQ(msvcrtModuleImports[22]->rvaOriginalThunk(), 0xE158);
            ASSERT_EQ(msvcrtModuleImports[22]->rvaThunk(), 0xE280);
            ASSERT_EQ(msvcrtModuleImports[22]->rvaOriginalThunkAddressOfData(), 0xE47A);
            ASSERT_EQ(msvcrtModuleImports[22]->rvaThunkAddressOfData(), 0xE47A);
            ASSERT_EQ(msvcrtModuleImports[22]->sizeOfThunk(), 0x8);
            ASSERT_EQ(pe->rvaToOffset(msvcrtModuleImports[22]->rvaOriginalThunk()), 0x9158);
        }
    }
}

