#include <gtest/gtest.h>
#include "../../../../src/shared/event/simple/SimpleEventBus.hpp"

class DummyEvent : public IEvent
{
public:
	std::string message;
	DummyEvent(const char* msg): message(std::string(msg)) {}
};

TEST(SimpleEventBusTest, HandlerWillBeCalledWithProperEvent) {
	auto eventBus = new CSimpleEventBus();
	auto publishedEvent = new DummyEvent("Test");

	bool gotCalled = false;
	eventBus->subscribe(typeid(DummyEvent), [&](IEvent* event) {
		auto dummyEvent = dynamic_cast<DummyEvent*>(event);
		gotCalled = true;
		ASSERT_STREQ(dummyEvent->message.c_str(), "Test");
		ASSERT_EQ(dummyEvent, publishedEvent);
	});

	eventBus->publish(publishedEvent);

	// wait till thread will handle event
	// if timeout raise exception
	int timer = 0;
	while (!gotCalled) {
		_sleep(1);
		timer++;
		if (timer > 500) {
			throw "Holly molly!";
		}
	}
}
