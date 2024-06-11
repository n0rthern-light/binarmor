#pragma once

#include "FileDropTarget.hpp"

CFileDropTarget::CFileDropTarget(file_drop_target_handler_fn handler) : m_handler(handler) {}

bool CFileDropTarget::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames)
{
    auto vec = vec_file_paths { }; 

    for (const auto& fileName : filenames) {
        vec.push_back(std::filesystem::path(std::string(fileName.c_str())));
    }

    m_handler(vec);

    return true;
}

