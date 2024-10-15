#include "NewFileSelectedEvent.hpp"

using namespace program::core::application::events;

CNewFileSelectedEvent::CNewFileSelectedEvent(const char* path)
{
    _path = std::string(path);
}

const std::string& CNewFileSelectedEvent::path()
{
    return _path;
}
