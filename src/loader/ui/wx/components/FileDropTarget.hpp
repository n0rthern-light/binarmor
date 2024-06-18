#ifndef LOADER_UI_WX_COMPONENTS__FILE_DROP_TARGET_HPP_
#define LOADER_UI_WX_COMPONENTS__FILE_DROP_TARGET_HPP_

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

#endif // LOADER_UI_WX_COMPONENTS__FILE_DROP_TARGET_HPP_
