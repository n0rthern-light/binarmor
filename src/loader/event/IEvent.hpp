#pragma once

#include <string>

class IEvent
{
public:
	virtual ~IEvent() {};
};

class TestEvent : public IEvent
{
public:
	std::string str;

	TestEvent(const char* _str)
	{
		str = std::string(_str);
	}
};
