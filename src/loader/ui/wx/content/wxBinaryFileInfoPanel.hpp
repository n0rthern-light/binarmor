#ifndef LOADER_UI_WX_CONTENT_WX_BINARY_FILE_INFO_PANEL_HPP_
#define LOADER_UI_WX_CONTENT_WX_BINARY_FILE_INFO_PANEL_HPP_

#include "../wx_headers.hpp"
#include "core/file/BinaryFile.hpp"
#include <shared/message/IMessageBus.hpp>
#include <map>

struct TextInfoRow_t
{
    std::string id;
    std::string label;
    std::string value;
};

class CwxBinaryFileInfoPanel : public wxPanel
{
    IMessageBus* m_eventBus;
    std::unique_ptr<wxBoxSizer> m_sizer;
    std::map<int, TextInfoRow_t> m_infoRows;

    void initInfoRows();
    int resolveKey(const std::string& id);
    void setLabel(const std::string& key, const std::string& label);
    void setInfo(const std::string& key, const std::string& value);
    void updateWxInfoRows();
    wxBoxSizer* createInfoRow(const TextInfoRow_t& row);
public:
    CwxBinaryFileInfoPanel(wxWindow* parent, IMessageBus* t_eventBus);
    void loadFileData(const program::core::file::CBinaryFile& binaryFile);
};

#endif // LOADER_UI_WX_CONTENT_WX_BINARY_FILE_INFO_PANEL_HPP_
