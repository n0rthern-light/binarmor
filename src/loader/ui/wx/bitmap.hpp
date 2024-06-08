#ifndef SRC_LOADER_UI_WX_BITMAP_HPP_
#define SRC_LOADER_UI_WX_BITMAP_HPP_

#include "wx_headers.hpp"
#include <vector>
#include <shared/RuntimeException.hpp>
#include <shared/self_obfuscation/strenc.hpp>

class Bitmap {
public:
    static wxBitmap CreateFromBuffer(const std::vector<unsigned char>& imageData, size_t imageSize = 48) {
        size_t imageDataLength = imageData.size();
        wxMemoryBuffer buffer;
        buffer.AppendData(imageData.data(), imageDataLength);

        wxMemoryInputStream input(buffer.GetData(), buffer.GetDataLen());
        wxImage image(input, wxBITMAP_TYPE_PNG);
        if (image.IsOk()) {
            image.Rescale(imageSize, imageSize);
            return wxBitmap(image);
        }
        else {
            throw RuntimeException(strenc("Could not load PNG bitmap"));
        }
    }
};



#endif // SRC_LOADER_UI_WX_BITMAP_HPP_
