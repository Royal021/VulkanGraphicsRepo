#pragma once 
#include "vkhelpers.h"
#include "imagedecode.h"
#include "imagescale.h"
#include "CommandBuffer.h"
#include <span>
#include <functional>

class StagingBuffer;
class Image;

namespace Images{

/// Initialize the subsystem.
/// @param ctx The context
void initialize(VulkanContext* ctx);

/// Return true if subsystem was initialized
/// @return True if initialized; false if not
bool initialized();


class Layer;

/// One mip level of an image. This is created by the Image object.
class Mip{
  public:
    /// Width of the mip
    unsigned width;
    
    /// Height of the mip
    unsigned height;
    
    /// pixel data for the mip; may be empty if image
    /// is uninitialized
    std::vector<char> pixels;

  private:
    /// Create a mip
    /// @param w Width
    /// @param h Height
    /// @param pixels Pixel data; might be empty if image is uninitialized
    Mip(int w, int h, std::span<const char> pixels);
    friend class Layer;
    friend class ::Image;
    VkImageLayout layout = VK_IMAGE_LAYOUT_UNDEFINED;
};

/// One layer of a multi-layer image. Each layer contains
/// one or more mip levels. This is created by the Image object.
class Layer{
  public:

    /// Width of layer
    unsigned width;
    
    /// Height of layer
    unsigned height;
    
    /// Each mip level of the layer
    std::vector<Mip> mips;
    
    /// Get a view of only this layer
    /// @return The view
    VkImageView view(); 
    
  private:
    Layer(int w, int h,std::span<const char> pixels);
    void makeMipPyramid();
    VkImageView view_ = VK_NULL_HANDLE;
    friend class ::Image;
};

}; //namespace


/// An image (texture or framebuffer attachment).
class Image{
  public:
    
    /// Memory requirements for this image
    VkMemoryRequirements memoryRequirements;
    
    /// Return the image's view. Requires that copyDataToGPU was
    /// called first. (See ImageManager).
    /// @return The view
    VkImageView view();
    
    /// Width of image
    unsigned width;
    
    /// Height of image
    unsigned height;
    
    /// Number of layers in image
    unsigned numLayers;
    
    /// The image object itself
    VkImage image;
    
    /// Storage format
    VkFormat format;
    
    /// Type of view
    VkImageViewType viewType;
    
    /// Name, for debugging
    std::string name;
    
    /// The layers in the image
    std::vector<Images::Layer> layers;
    
    /// The desired layout of the image after initialization is complete
    VkImageLayout finalLayout;
    
    /// Image aspect (ex: Is image a color texture, depth texture, etc.)
    VkImageAspectFlags aspect;

    /// Constructor (Usually, images will be created using ImageManager
    /// functions and not created using this function directly).
    /// @param width Image width
    /// @param height Image height
    /// @param numLayers Number of layers
    /// @param format Image format
    /// @param usage How image will be used
    /// @param flags Creation flags
    /// @param viewType Image's view type
    /// @param aspect Image's aspect
    /// @param pixels Initial data; one entry per layer (if uninitialized, the span may be empty)
    /// @param name For debugging
    Image(
        unsigned width, unsigned height, unsigned numLayers,
        VkFormat format, VkImageUsageFlags usage,
        VkImageCreateFlags flags, VkImageViewType viewType,
        VkImageLayout finalLayout, VkImageAspectFlags aspect,
        const std::vector< std::span<const char> >& pixels,
        std::string name
    );
        
        
    /// Clean up image resources
    void cleanup();
    
    /// Copy image data to GPU and allocate its view.
    /// @param stagingBuffer Staging buffer to use for temporary storage.
    ///                      This must be large enough for the Image's data
    /// @param memory The memory destination for the copy
    /// @param startingOffset Offset within the memory for this image's data
    void copyDataToGPU(StagingBuffer* stagingBuffer, VkDeviceMemory memory, VkDeviceSize startingOffset);
    
    /// Add callback to be called when this Image is copied to the GPU and gets its view.
    /// If the Image has already been copied to the GPU when addCallback is executed,
    /// the callback is called immediately.
    /// @param f The callback. It receives this Image as an argument.
    void addCallback( std::function<void(Image*)> f );
    
    /// Perform a layout transition on this image: Transition all mips of all layers.
    /// Do the operation immediately using a temporary command buffer.
    /// @param newLayout the new layout
    void layoutTransition(VkImageLayout newLayout);

    /// Perform a layout transition on this image: Transition all mips of all layers.
    /// Add the layout transition commands to the given command buffer.
    /// @param newLayout the new layout
    /// @param cmd The command buffer
    void layoutTransition(VkImageLayout newLayout_, VkCommandBuffer cmd);

    /// Perform a layout transition on this image: Transition a single layer and mip level
    /// Do the operation immediately using a temporary command buffer.
    /// @param layer The layer to process
    /// @param mipLevel The mip level to process
    /// @param newLayout the new layout
    void layoutTransition(unsigned layer, unsigned mipLevel, VkImageLayout newLayout);

    /// Perform a layout transition on this image: Transition a single layer and mip level
    /// Add the layout transition commands to the given command buffer.
    /// @param layer The layer to process
    /// @param mipLevel The mip level to process
    /// @param newLayout the new layout
    /// @param cmd The command buffer
    void layoutTransition(unsigned layer, unsigned mipLevel, 
            VkImageLayout newLayout, VkCommandBuffer cmd);


    /// Perform a layout transition on this image: Transition 
    /// some subset of layers and mips.
    /// Add the layout transition commands to the given command buffer.
    /// @param firstLayer The first layer to process
    /// @param numLayers Number of layers to process
    /// @param firstMip The first mip level to process
    /// @param numMips Number of mip levels to process
    /// @param newLayout the new layout
    /// @param cmd The command buffer
    void layoutTransition(unsigned firstLayer, unsigned numLayers,
                          unsigned firstMip, unsigned numMips,
                          VkImageLayout newLayout, VkCommandBuffer cmd);
                          
    /// Perform a layout transition on this image: Transition 
    /// some subset of layers and mips using the given aspect.
    /// Add the layout transition commands to the given command buffer.
    /// @param aspect The aspect to use.
    /// @param firstLayer The first layer to process
    /// @param numLayers Number of layers to process
    /// @param firstMip The first mip level to process
    /// @param numMips Number of mip levels to process
    /// @param newLayout the new layout
    /// @param cmd The command buffer
    void layoutTransition( VkImageAspectFlags aspect, unsigned firstLayer, unsigned numLayers,
            unsigned firstMip, unsigned numMips, VkImageLayout newLayout,  VkCommandBuffer cmd );
            
    /// Check if image has been copied to GPU.
    /// @return True if image has been copied to GPU and has a view.
    bool pushedToGPU();
    
  private:
    Image(const Image&) = delete;
    void operator=(const Image&) = delete;
    VkImageView view_=VK_NULL_HANDLE;
    std::vector<VkImageLayout> currentLayout;
    std::vector<std::function<void(Image*)> > callbacks;
    bool allLayoutsMatch(  unsigned firstLayer, unsigned numLayers,
        unsigned firstMip, unsigned numMips);
};
  

