#include <gtest/gtest.h>
#include <core/application/events/NewFileSelectedEvent.hpp>

TEST(NewFileSelectedTest, GetterReturnsCorrectPath) {
    auto event = std::make_unique<CNewFileSelectedEvent>("C:\\System32\\kernel32.dll");

    ASSERT_STREQ(event->path().c_str(), "C:\\System32\\kernel32.dll");
}
