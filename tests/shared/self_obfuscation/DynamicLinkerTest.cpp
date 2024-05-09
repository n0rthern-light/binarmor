#include <gtest/gtest.h>
#include <shared/self_obfuscation/DynamicLinker.hpp>
#include <shared/self_obfuscation/win_api.hpp>
#include <shared/RuntimeException.hpp>

TEST(DynamicLinkerTest, WillProperlyResolveKernel32GetModuleFileNameA) {
	auto linker = new CDynamicLinker();

	auto fn = linker->GetFunction("KERNEL32.DLL", "GetModuleFileNameA");

#if defined(_WIN64)
	DWORD expectedRva = 0x2BB0;
#elif defined(_WIN32)
	DWORD expectedRva = 0x3430;
#endif

	ASSERT_EQ(fn->rva, expectedRva);

    char buffer[MAX_PATH];
    DWORD length = fn->call<pGetModuleFileNameA>((HMODULE)NULL, buffer, MAX_PATH);

    std::string exeName = "";
    if (length != 0) {
        std::string fullPath(buffer);

        size_t pos = fullPath.find_last_of("\\/");
        if (pos != std::string::npos) {
            exeName = fullPath.substr(pos + 1);
        }
        else {
            exeName = fullPath;
        }
    }

    ASSERT_STREQ(exeName.c_str(), "DynamicLinkerTest.exe");
}

TEST(DynamicLinkerTest, WillThrowExceptionWhenInvalidFunctionRequested) {
	auto linker = new CDynamicLinker();

    try {
        linker->GetFunction("KERNEL32.DLL", "TotallyInvalidFunction");
        FAIL() << "Expected RuntimeException";
    }
    catch (const RuntimeException& e) {
        EXPECT_STREQ(e.what(), "Failed to LoadFunction: TotallyInvalidFunction");
    }
    catch (...) {
        FAIL() << "Expected RuntimeException";
    }
}
