#include "NewFileSelectedEvent.hpp"

using namespace program::core::application::events;

CNewFileSelectedEvent::CNewFileSelectedEvent(const char* path)
{
    m_path = std::string(path);
}

const std::string& CNewFileSelectedEvent::path()
{
    return m_path;
}
