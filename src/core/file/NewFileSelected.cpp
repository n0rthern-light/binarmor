#include "NewFileSelected.hpp"

CNewFileSelected::CNewFileSelected(const char* _path)
{
	path = std::string(_path);
}

const std::string& CNewFileSelected::getPath()
{
	return path;
}
