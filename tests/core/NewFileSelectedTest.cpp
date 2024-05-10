#include <gtest/gtest.h>
#include <core/file/NewFileSelected.hpp>

TEST(NewFileSelectedTest, GetterReturnsCorrectPath) {
	auto event = new CNewFileSelected("C:\\System32\\kernel32.dll");

	ASSERT_STREQ(event->getPath().c_str(), "C:\\System32\\kernel32.dll");
}
