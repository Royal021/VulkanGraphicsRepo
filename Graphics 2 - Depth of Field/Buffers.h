#pragma once
#include "vkhelpers.h"

/** Wrapper for a VkBuffer. Subclasses exist for host-visible staging buffers (StagingBuffer)
 * and device-local buffers (DeviceLocalBuffer).
 */
class Buffer{
    /// Buffers may not be copied once created.
    Buffer(const Buffer&) = delete;
    void operator=(const Buffer&) = delete;
  public:
  
    VulkanContext* ctx;             ///< The VulkanContext associated with this buffer.
    VkBuffer buffer;                ///< The actual wrapped Vulkan buffer itself.
    VkDeviceMemory memory = VK_NULL_HANDLE; ///< Memory associated with the buffer.
    bool ownsMemory=false;          ///< True if this buffer owns the memory (and will free it on cleanup).
    VkDeviceSize byteSize;          ///< Size of the buffer's data in bytes.
    std::string name;               ///< Name for debugging purposes.
    VkMemoryRequirements memoryRequirements;    ///< Memory requirements for the buffer; this is set by the constructor.
 
    /// Create a buffer object.
    /// @param ctx The owning VulkanContext
    /// @param usage Tells how the buffer will be used
    /// @param size The size of the buffer, in bytes
    /// @param name Name for debugging purposes.
    Buffer(VulkanContext* ctx, VkBufferUsageFlags usage, VkDeviceSize size, const std::string& name);
    
    /// Associate a block of memory with this buffer
    /// @param memory The memory block to use
    /// @param offset Starting location in the memory region
    /// @param ownsMemory True if this Buffer should take ownership of the memory (and free it upon Buffer cleanup).
    void bindMemory(VkDeviceMemory memory, VkDeviceSize offset, bool ownsMemory);
    
    /// Free all resources associated with this buffer. If the buffer owns the associated memory, free that as well.
    void cleanup();
    
    /// Copy this buffer's contents to some other buffer.
    void copyTo(Buffer* otherBuffer);
    
    /// Insert a memory barrier into the given command buffer. This is a full memory barrier,
    /// which is more conservative (and slower) than it might need to be.
    /// @param cmd The command buffer to use.
    void memoryBarrier(VkCommandBuffer cmd);
    
    /// Make a view of this buffer. The view covers the entire buffer.
    /// @param fmt The format to be used in the view.
    /// @return The view itself; it will be automatically cleaned up upon program exit.
    VkBufferView makeView(VkFormat fmt);
};
    
    
/// A staging buffer is one which is visible and accessible on the host. In particular,
/// it may be mapped for host access.
class StagingBuffer: public Buffer{
    StagingBuffer(const StagingBuffer&) = delete;
    void operator=(const StagingBuffer&) = delete;
  public:
  
    /// Create a staging buffer from some optional initial data.
    /// @param ctx The owning context
    /// @param initialData The data to use for initializing the buffer (may be null).
    /// @param size Size in bytes of the buffer
    /// @param name Name for debugging use.
    StagingBuffer(VulkanContext* ctx, const void* initialData, VkDeviceSize size, const std::string& name);
    
    /// Create a staging buffer from a vector of data.
    /// @param ctx The owning context
    /// @param v The data to use for initializing the buffer
    /// @param name Name for debugging use.
    template<typename T>
    StagingBuffer(VulkanContext* ctx_, const std::vector<T>& v, const std::string& name_) : StagingBuffer(ctx,v.data(),v.size()*sizeof(T), name_){}

    /// Map the buffer into the host's memory space. Call unmap() to release the mapping.
    /// @return A pointer to the mapped data
    void* map();
    
    /// Unmap the buffer. This assumes map() was called first.
    void unmap();
    
    /// Clean up any buffer resources. See Buffer::cleanup for more details.
    void cleanup();
};
 
 
/// A device-local buffer is typically located in the highest-speed
/// RAM available to the GPU, but it cannot be directly accessed from the
/// host CPU.
class DeviceLocalBuffer: public Buffer{
    DeviceLocalBuffer(const DeviceLocalBuffer&) = delete;
    void operator=(const DeviceLocalBuffer&) = delete;
    
  public:
  
  
    /// Create a device-local buffer from some optional initial data.
    /// @param ctx The owning context
    /// @param initialData The data to use for initializing the buffer (may be null).
    /// @param size Size in bytes of the buffer
    /// @param usage Usage flags (ex: VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
    /// @param name Name for debugging.
    DeviceLocalBuffer(VulkanContext* ctx, const void* initialData, 
                      VkDeviceSize size, VkBufferUsageFlags usage,
                      const std::string& name);
 
 
    /// Create a device-local buffer from a pre-existing memory allocation.
    /// @param ctx The owning context
    /// @param memory The memory to use; the buffer will not take ownership of this memory block.
    /// @param offset Starting offset in the memory for the buffer
    /// @param size Size in bytes of the buffer
    /// @param usage Usage flags (ex: VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
    /// @param name Name for debugging.
    DeviceLocalBuffer(VulkanContext* ctx, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkBufferUsageFlags usage,
        const std::string& name);
       
    /// Create a device-local buffer from a vector of data.
    /// @param ctx The owning context
    /// @param v The data to use for initializing the buffer
    /// @param usage Usage flags (ex: VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
    /// @param name Name for debugging use.
    template<typename T>
    DeviceLocalBuffer(VulkanContext* ctx_, const std::vector<T>& v, VkBufferUsageFlags usage, const std::string& name_): 
        DeviceLocalBuffer(ctx_,v.data(),v.size()*sizeof(T),usage,name_){}

    /// Allocate a block of memory suitable for a DeviceLocalBuffer
    /// @param ctx The owning context
    /// @param memoryTypeBits Bitmask of allowable memory types; obtain this from the VkMemoryRequirements struct
    /// @param size Size in bytes
    /// @param name Name for debugging purposes
    static VkDeviceMemory allocateMemory(VulkanContext* ctx,
                        std::uint32_t memoryTypeBits,
                        VkDeviceSize size, std::string name);
    
    /// Clean up the buffer's resources; see Buffer::cleanup() for more details.
    void cleanup();
    
    
};


namespace Buffers{


/// Helper function to allocate a block of memory
/// @param ctx The owning context
/// @param memoryTypeBits Bitmask of allowable memory types; obtain this from the VkMemoryRequirements struct
/// @param size Size in bytes
/// @param properties Memory properties (ex: VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
/// @param name Name, for debugging
/// @returns The memory object.
VkDeviceMemory allocateMemory(
    VulkanContext* ctx,
    std::uint32_t memoryTypeBits,
    VkDeviceSize size,
    VkMemoryPropertyFlags properties, 
    const std::string& name);
    
/// Insert a memory barrier into a command buffer for a particular buffer.
/// @param cmd THe command buffer
/// @param buffer the buffer to be protected
void memoryBarrier(VkCommandBuffer cmd, VkBuffer buffer);

};  //namespace
