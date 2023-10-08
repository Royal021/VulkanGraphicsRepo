#pragma once
#include "vkhelpers.h"
#include "Images.h"
#include <array>

namespace ImageManager{
    
/// Initialize the subsystem.
/// @param ctx The context
void initialize(VulkanContext* ctx);

/// Return true if subsystem was initialized
/// @return True if initialized; false if not
bool initialized();


/// Load an image from a file (PNG, JPEG, etc.)
/// @param filename Name of the file to load
///         If this function is called twice with the same
///         filename, the same Image object is returned both times.
/// @return The image.
Image* load(std::string filename);

/// Load an image (PNG, JPEG, etc.) from memory
/// @param data The encoded image data
/// @param name Name of the data. If this function is called twice with
///             the same name, the same Image object is returned both times.
/// @return The image.
Image* loadFromData(std::span<const char> data, std::string name );

/// Load an image (PNG, JPEG, etc.) from memory
/// @param data The encoded image data
/// @param name Name of the data  If this function is called twice with
///             the same name, the same Image object is returned both times.
/// @return The image.
Image* loadFromData(const std::vector<char>& data, std::string name);

/// Create a 1x1 solid color image
/// @param r,g,b,a The pixel values; typically in 0...1 range. 
///             If this function is called twice with the same r,g,b,a
///             values, the same Image object is returned both times.
/// @return The image.
Image* createSolidColorImage(float r, float g, float b, float a);

/// Load a cube map from files
/// @param filenames Array of 6 images in the order +x, -x, +y, -y, +z, -z
///             If this function is called twice with
///             the same names in the same order, the same Image
///             object is returned both times.
/// @return The image.
Image* loadCube(std::array<std::string,6> filenames);

/// Create an image with unspecified initial contents
/// @param w Width
/// @param w Height
/// @param numLayers Number of layers
/// @param format Format of the image
/// @param usage Usage flags (ex: VK_IMAGE_USAGE_SAMPLED_BIT)
/// @param viewType View type (ex: VK_IMAGE_VIEW_TYPE_2D_ARRAY)
/// @param finalLayout Layout of the image object (ex: VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
/// @param aspect Image aspect (ex: VK_IMAGE_ASPECT_COLOR_BIT)
/// @param name Name, for debugging. Unlike the other image loading functions,
///             this function always returns a unique Image object,
///             even for multiple calls with the same name.
/// @param name Name of the data, for debugging.
/// @return The image.
Image* createUninitializedImage(
    int w, int h, int numLayers,
    VkFormat format, VkImageUsageFlags usage,
    VkImageViewType viewType,
    VkImageLayout finalLayout, VkImageAspectFlags aspect,
    std::string name
);

/// Transfer all image data to the GPU and create view's for them.
/// This may be called more than once, but it is more efficient to
/// call it only once. Images that have already been transferred to
/// the GPU are left unchanged.
void pushToGPU();

/// Add a callback that will be executed *each* time pushToGPU is called
/// and at least one image is transferred to the GPU.
/// @param f The callback.
void addCallback( std::function<void(void)> f);

}
  

