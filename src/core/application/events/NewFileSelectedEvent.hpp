#pragma once

#include <shared/message/IMessage.hpp>
#include <string>

class CNewFileSelectedEvent : public IMessage
{
	std::string _path;

public:
	CNewFileSelectedEvent(const char* path);
	const std::string& path();
};
