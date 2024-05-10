#pragma once

#include <shared/event/IEvent.hpp>
#include <string>

class CNewFileSelected : public IEvent
{
	std::string path;

public:
	CNewFileSelected(const char* _path);
	const std::string& getPath();
};