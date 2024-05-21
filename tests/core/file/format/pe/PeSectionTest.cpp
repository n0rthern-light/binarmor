#include <gtest/gtest.h>
#include "../../BinaryMother.hpp"

auto x86exe_Sections = BinaryMother::x86exe()->getSections();
auto x86dll_Sections = BinaryMother::x86dll()->getSections();
auto x86_64exe_Sections = BinaryMother::x86_64exe()->getSections();
auto x86_64dll_Sections = BinaryMother::x86_64dll()->getSections();

#define ASSERT_SECTION_NAMES(sections, names)					 \
        i = 0;													 \
        for (auto name : names) {                                \
			std::string currentNameStr = sections[i]->getName(); \
            const char* currentName = currentNameStr.c_str();    \
            ASSERT_STREQ(currentName, name);				     \
            i++;												\
        }														\

TEST(PeSectionTest, NamesAreCorrectlyResolved)
{
	unsigned int i = 0;

	{
		SCOPED_TRACE("Testing x86exe");
		const char* x86exe_Names[BINARY_MOTHER_X86_EXE_SECTION_COUNT] = { ".text", ".data", ".rdata", ".bss", ".idata", ".CRT", ".tls", ".reloc", "/4", "/19", "/31", "/45", "/57", "/70", "/81", "/97", "/113" };

		ASSERT_SECTION_NAMES(x86exe_Sections, x86exe_Names);
	}

	{
		SCOPED_TRACE("Testing x86dll");
		const char* x86dll_Names[BINARY_MOTHER_X86_DLL_SECTION_COUNT] = { ".text", ".data", ".rdata", ".bss", ".edata", ".idata", ".CRT", ".tls", ".reloc", "/4", "/19", "/31", "/45", "/57", "/70", "/81", "/97", "/113" };

		ASSERT_SECTION_NAMES(x86dll_Sections, x86dll_Names);
	}

	{
		SCOPED_TRACE("Testing x86_64exe");
		const char* x86_64exe_Names[BINARY_MOTHER_X86_64_EXE_SECTION_COUNT] = { ".text", ".data", ".rdata", ".pdata", ".xdata", ".bss", ".idata", ".CRT", ".tls", ".reloc", "/4", "/19", "/31", "/45", "/57", "/70", "/81", "/97", "/113" };

		ASSERT_SECTION_NAMES(x86_64exe_Sections, x86_64exe_Names);
	}

	{
		SCOPED_TRACE("Testing x86_64dll");
		const char* x86_64dll_Names[BINARY_MOTHER_X86_64_DLL_SECTION_COUNT] = { ".text", ".data", ".rdata", ".pdata", ".xdata", ".bss", ".edata", ".idata", ".CRT", ".tls", ".reloc", "/4", "/19", "/31", "/45", "/57", "/70", "/81", "/97", "/113" };

		ASSERT_SECTION_NAMES(x86_64dll_Sections, x86_64dll_Names);
	}
}

