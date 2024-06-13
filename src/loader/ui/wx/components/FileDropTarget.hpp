#pragma once

#include "../wx_headers.hpp"
#include <functional>
#include <filesystem>
#include <vector>

using vec_file_paths = std::vector<std::filesystem::path>;
using file_drop_target_handler_fn = std::function<void(const vec_file_paths)>;

class CFileDropTarget : public wxFileDropTarget {
public:
    CFileDropTarget(file_drop_target_handler_fn handler);
    virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames) override;
private:
    file_drop_target_handler_fn m_handler;
};

