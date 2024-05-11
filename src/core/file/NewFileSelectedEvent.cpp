#include "NewFileSelectedEvent.hpp"

CNewFileSelectedEvent::CNewFileSelectedEvent(const char* _path)
{
	path = std::string(_path);
}

const std::string& CNewFileSelectedEvent::getPath()
{
	return path;
}
