#include "vkhelpers.h"
#include <functional>

//low level utilities that don't fit elsewhere

namespace utils{

/// Call this at the start of the draw function. It calls any
/// pending frame complete callbacks that have been registered
/// (see registerFrameCompleteCallback()).
/// @param ctx The context
/// @return A command buffer that can be used for rendering
VkCommandBuffer beginFrame(VulkanContext* ctx);

/// Call this at the end of the draw function
/// @param ctx The context
void endFrame(VulkanContext* ctx);

/// Get the current swapchain image index
/// @return The image index
int getSwapchainImageIndex();

/// Compute padding for uniforms or push constants
/// @param offset Current offset within file
/// @param alignment Desired alignment of next item to add
/// @return Number of bytes of padding that need to be added to
///        offset to make it a multiple of alignment.
int computePadding( VkDeviceSize offset, VkDeviceSize alignment );

/// Read the contents of a file. Throws an exception if the
/// file cannot be read.
/// @param filename The file to read
/// @return The file's data
std::vector<char> readFile(std::string filename);

/// Register a callback to be notified when a particular
/// frame has completely finished rendering.
/// The check for frame completeness is performed at the very start of beginFrame()
/// so that we have the best chance of finding any previous frames that
/// have progressed entirely thorough the GPU pipeline.
/// The callback is passed the identifier of the frame that
/// has been completed (see getCurrentFrameIdentifier()).
/// @param f The callback
void registerFrameCompleteCallback( std::function<void(unsigned)> f);

/// Get a unique identifier for the current frame. This eventually
/// wraps after approximately 4.2 billion frames have been rendered.
/// This identifier is used in the registerFrameCallback() callback.
/// This function may only be called between beginFrame() and endFrame().
/// @return The frame identifier.
unsigned getCurrentFrameIdentifier();

/// Register a callback to be notified at the start of frame rendering.
/// It is passed the swapchain image index and the command buffer.
/// @param The callback
void registerFrameBeginCallback(  std::function<void(int,VkCommandBuffer)> f);

/// Register a callback to be notified at the end of frame rendering.
/// This is called just before the command buffer is submitted to the queue.
/// It is passed the swapchain image index and the command buffer.
/// @param The callback
void registerFrameEndCallback(  std::function<void(int,VkCommandBuffer)> f);

};
