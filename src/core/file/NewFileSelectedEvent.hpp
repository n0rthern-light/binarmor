#pragma once

#include <shared/event/IEvent.hpp>
#include <string>

class CNewFileSelectedEvent : public IEvent
{
	std::string path;

public:
	CNewFileSelectedEvent(const char* _path);
	const std::string& getPath();
};