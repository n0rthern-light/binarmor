#include "wxApp.hpp"

bool CwxApp::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler());

    return true;
}
