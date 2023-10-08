#pragma once

#include <vector>
#include <string>

namespace imageencode{
    
/// Encode image data to a PNG
/// @param w width
/// @param h height
/// @param fmt Image format (must be RGBA8 or RGB8)
/// @param data The pixel data
/// @return The PNG data
std::vector<char> encodePNG(int w, int h, std::string fmt, const std::vector<char>& data);


};
