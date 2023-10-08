#include "SDL.h"
#include <vector>
#include <cassert>
#include <cstring>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "ext/stb_image_resize.h"


namespace imagescale {
    
std::vector<char> scaleImage(int w, int h, std::vector<char>& pix, int scaledWidth, int scaledHeight)
{
    std::vector<char> dpix(scaledWidth*4*scaledHeight);
    stbir_resize_uint8( (unsigned char*) pix.data(), w,h, 0,
                        (unsigned char*) dpix.data(), scaledWidth, scaledHeight, 0,
                        4 );
    return dpix;
}

};  //namespace

/*
static void copySurfaceToByteArray(SDL_Surface* surf, int width, int height, std::vector<char>& destinationArray)
{
    assert(width > 0);
    assert(width < 32768);
    assert(height > 0 );
    assert(height < 32768);
    
    SDL_LockSurface( surf );
    
    char* sourcePixels = (char*)surf->pixels;
    auto pitch = surf->pitch;
    
    assert((int)destinationArray.size() >= width*height*4 );
    char* destAddress = destinationArray.data();
    
    int soffset=0;
    int doffset=0;
    int rowsize=width*4;
    for(int y=0;y<height;++y){
        std::memmove(destAddress+doffset, sourcePixels+soffset, rowsize);
        soffset += pitch;
        doffset += rowsize;
    }
    
    SDL_UnlockSurface( surf );
}

static void copyImageToSurface(int w,int h,std::vector<char>& pix, SDL_Surface* sourceSurface)
{
    assert(w > 0);
    assert(w < 32768);
    assert(h > 0 );
    assert(h < 32768);
    SDL_LockSurface( sourceSurface );
    char* ptr = (char*)sourceSurface->pixels;
    auto pitch = sourceSurface->pitch;
    char* srcAddr = pix.data();
    int offset=0;
    int rowsize=w*4;
    for(int y=0;y<h;++y){
        memmove(ptr+offset,srcAddr,rowsize);
        offset += pitch;
        srcAddr += rowsize;
    }
    SDL_UnlockSurface( sourceSurface );
}


namespace imagescale {
    
std::vector<char> scaleImage(int w, int h, std::vector<char>& pix, int scaledWidth, int scaledHeight)
{
    assert(w > 0);
    assert(w < 32768);
    assert(h > 0 );
    assert(h < 32768);
    
    
    std::vector<char> dpix;
    
    if( pix.empty() ){
        dpix.resize(scaledWidth*scaledHeight*4);
        return dpix;
    }
    
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "best" );
    auto sourceSurface = SDL_CreateRGBSurface(
        0, w,h, 32, 0xff, 0xff00, 0xff0000, 0xff000000
    );
    auto destSurface = SDL_CreateRGBSurface(
        0, scaledWidth,scaledHeight, 32, 0xff, 0xff00, 0xff0000, 0xff000000
    );
    auto renderer = SDL_CreateSoftwareRenderer(destSurface);
    copyImageToSurface(w,h,pix,sourceSurface);
    auto sourceTexture = SDL_CreateTextureFromSurface(renderer, sourceSurface);
    SDL_RenderCopyExF( 
        renderer, 
        sourceTexture,        //source texture
        nullptr,           //source rect
        nullptr,           //dest rect
        0,      //angle
        nullptr,   //center of rotation
        SDL_FLIP_NONE
    );
    
    dpix.resize(scaledWidth*scaledHeight*4);
    copySurfaceToByteArray(destSurface,scaledWidth,scaledHeight,dpix);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(sourceTexture);
    SDL_FreeSurface(sourceSurface);
    SDL_FreeSurface(destSurface);
    return dpix;
}

}; //end namespace
  
 */
