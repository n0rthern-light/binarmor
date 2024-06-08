#ifndef LOADER_UI_WX_WX_APP_HPP_
#define LOADER_UI_WX_WX_APP_HPP_

#include "wx_headers.hpp"

class CwxApp : public wxApp
{
public:
    virtual bool OnInit() override;
};

#endif // LOADER_UI_WX_WX_APP_HPP_
