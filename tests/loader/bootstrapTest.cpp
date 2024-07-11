#include <cstdlib>
#include <gtest/gtest.h>
#include <loader/bootstrap.hpp>
#include <shared/application/container.hpp>
#include <core/application/container.hpp>
#include <loader/application/container.hpp>

TEST(bootstrapTest, DISABLED_programCanBeBootstrapped)
{
    ASSERT_EQ(program::shared::container::eventBus, nullptr);
    ASSERT_EQ(program::core::container::file::binaryFileStateManager, nullptr);
    ASSERT_EQ(program::loader::container::guiApp, nullptr);

    program::bootstrap::init(0, nullptr);

    ASSERT_NE(program::shared::container::eventBus, nullptr);
    ASSERT_NE(program::core::container::file::binaryFileStateManager, nullptr);
    ASSERT_NE(program::loader::container::guiApp, nullptr);
}

