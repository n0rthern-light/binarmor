#include <gtest/gtest.h>
#include <loader/container.hpp>


TEST(containerTest, ContainerWillBeInitializedProperly)
{
	ASSERT_EQ(container::eventBus, nullptr);
	ASSERT_EQ(container::guiApp, nullptr);

	container::init(0, nullptr, true);

	ASSERT_NE(container::eventBus, nullptr);
}
