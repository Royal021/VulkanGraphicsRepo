
namespace imagescale {
    
/// Scale an image
/// @param w Width
/// @param h Height
/// @param pix The raw pixel data, in row-major order, without padding
/// @param scaledWidth Width of scaled image
/// @param scaledHeight Height of scaled image
/// @return The scaled image data
std::vector<char> scaleImage(int w, int h, std::vector<char>& pix, int scaledWidth, int scaledHeight);

};
