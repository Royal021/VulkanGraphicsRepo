#define _CRT_SECURE_NO_WARNINGS

#include "imageencode.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "ext/stb_image_write.h"

#include <stdexcept>

static void callback(void* ctx, void* data, int size)
{
    std::vector<char>* p = (std::vector<char>*)ctx;
    char* c = (char*)data;
    p->insert(p->end(),c,c+size);
}

std::vector<char> imageencode::encodePNG(int w, int h, std::string fmt, const std::vector<char>& data)
{
    std::vector<char> pngdata;
    int components;
    if( fmt == "RGBA8" )
        components = 4;
    else if( fmt == "RGB8" )
        components = 3;
    else
        throw std::runtime_error("Format must be 'RGBA8' or 'RGB8'");

    stbi_write_png_to_func(callback, &pngdata, w,h, components ,  data.data(), w*components);
    return pngdata;
}

       
