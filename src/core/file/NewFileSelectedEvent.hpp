#pragma once

#include <shared/event/IEvent.hpp>
#include <string>

class CNewFileSelectedEvent : public IEvent
{
	std::string _path;

public:
	CNewFileSelectedEvent(const char* path);
	const std::string& path();
};
