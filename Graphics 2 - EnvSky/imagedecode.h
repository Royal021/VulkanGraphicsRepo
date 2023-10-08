#pragma once

#include <tuple>
#include <span>
#include <vector>
#include <string>

namespace imagedecode{
    
/// Decode image data
/// @param data The image data
/// @return Tuple: width, height, format ("RGBA8"), and the pixel data
std::tuple<int,int,std::string,std::vector<char>> decode(const std::vector<char>& data);

/// Decode image data
/// @param data The image data
/// @return Tuple: width, height, format ("RGBA8"), and the pixel data
std::tuple<int,int,std::string,std::vector<char>> decode(std::span<const char> data);

};
