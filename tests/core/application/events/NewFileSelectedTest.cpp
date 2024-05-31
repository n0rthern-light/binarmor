#include <gtest/gtest.h>
#include <core/application/events/NewFileSelectedEvent.hpp>

TEST(NewFileSelectedTest, GetterReturnsCorrectPath) {
	auto event = new CNewFileSelectedEvent("C:\\System32\\kernel32.dll");

	ASSERT_STREQ(event->path().c_str(), "C:\\System32\\kernel32.dll");
}
