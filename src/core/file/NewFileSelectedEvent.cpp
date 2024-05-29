#include "NewFileSelectedEvent.hpp"

CNewFileSelectedEvent::CNewFileSelectedEvent(const char* path)
{
	_path = std::string(path);
}

const std::string& CNewFileSelectedEvent::path()
{
	return _path;
}
