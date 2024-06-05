#include <gtest/gtest.h>
#include <shared/message/simple/SimpleMessageBus.hpp>

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

    ASSERT_TRUE(gotCalled);
}

