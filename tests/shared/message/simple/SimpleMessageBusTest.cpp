#include <gtest/gtest.h>
#include <shared/message/simple/SimpleMessageBus.hpp>
#include <chrono>
#include <thread>

class DummyEvent : public IMessage
{
public:
	std::string message;
	DummyEvent(const char* msg): message(std::string(msg)) {}
};

TEST(SimpleEventBusTest, HandlerWillBeCalledWithProperEvent) {
	auto eventBus = new CSimpleMessageBus();
	auto publishedEvent = std::make_shared<DummyEvent>("Test");

	bool gotCalled = false;
	eventBus->subscribe(typeid(DummyEvent), [&](message_ptr event) {
		auto dummyEvent = dynamic_cast<DummyEvent*>(event.get());
		gotCalled = true;
		ASSERT_STREQ(dummyEvent->message.c_str(), "Test");
		ASSERT_EQ(dummyEvent, publishedEvent.get());
	});

	eventBus->publish(publishedEvent);

	// wait till thread will handle event
	// if timeout raise exception
	int timer = 0;
	while (!gotCalled) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
		timer++;
		if (timer > 500) {
			throw "Holly molly!";
		}
	}
}

