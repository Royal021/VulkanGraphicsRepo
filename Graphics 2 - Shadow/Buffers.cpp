#include "Buffers.h"
#include "CommandBuffer.h"
#include <cstring>
#include <assert.h>
#include <stdexcept>


Buffer::Buffer(VulkanContext* ctx_, VkBufferUsageFlags usage, VkDeviceSize size, const std::string& name_)
{
    this->ctx=ctx_;
    this->name=name_;
    assert(size>0);
    check(vkCreateBuffer(
        ctx->dev,
        VkBufferCreateInfo{
            .sType=VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .pNext=nullptr,
            .flags=0,
            .size = (unsigned)size,
            .usage = usage,
            .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
            .queueFamilyIndexCount=0,
            .pQueueFamilyIndices=nullptr,
        },
        nullptr,
        &(this->buffer)
    ));
    this->byteSize=size;
    vkGetBufferMemoryRequirements( this->ctx->dev, this->buffer, &(this->memoryRequirements));
    ctx->setObjectName(this->buffer,name_);
}

void Buffer::memoryBarrier(VkCommandBuffer cmd)
{
    Buffers::memoryBarrier(cmd,this->buffer);
}

void Buffer::bindMemory(VkDeviceMemory memory_, VkDeviceSize offset, bool ownsMemory_)
{

    this->memory = memory_;
    this->ownsMemory = ownsMemory_;

    //safety check
    if(offset % this->memoryRequirements.alignment != 0)
        throw std::runtime_error("Buffer alignment error");
    vkBindBufferMemory(ctx->dev,this->buffer,memory,offset);
}

VkBufferView Buffer::makeView(VkFormat format)
{
    VkBufferViewCreateInfo cinfo{
        .sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .buffer= this->buffer,
        .format= format,
        .offset= 0,
        .range = VK_WHOLE_SIZE
    };
    VkBufferView v;
    check(
        vkCreateBufferView(
            this->ctx->dev,
            &cinfo,
            nullptr,    //allocators
            &v
        )
    );
    return v;
}


void Buffer::cleanup()
{
    vkDestroyBuffer(ctx->dev,this->buffer,nullptr);
    if( this->ownsMemory )
        vkFreeMemory( ctx->dev, this->memory, nullptr);
}

void Buffer::copyTo(Buffer* otherBuffer)
{
    auto cmd = CommandBuffer::beginImmediateCommands();
        vkCmdCopyBuffer(
            cmd,
            this->buffer,
            otherBuffer->buffer,
            1,
            VkBufferCopy{
                .srcOffset=0,
                .dstOffset=0,
                .size=this->byteSize
            }
        );
        Buffers::memoryBarrier(cmd,otherBuffer->buffer);
    CommandBuffer::endImmediateCommands(cmd);
}


StagingBuffer::StagingBuffer(VulkanContext* ctx_, const void* initialData, VkDeviceSize size, const std::string& name_):
    Buffer(
        ctx_,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT|VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        size,
        name_
    )
{
    //get memory requirements for the buffer
    //This tells us three things:
    //The size, alignment, and memory types
    //If bit i of memoryTypeBits is set,
    //then type i is OK to use

    VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    this->memory = Buffers::allocateMemory(
        ctx,
        this->memoryRequirements.memoryTypeBits,
        this->memoryRequirements.size,
        properties,
        "Memory for buffer{"+name+"}"
    );
    this->bindMemory(this->memory,0,true);

    if(initialData != nullptr){
        auto p = this->map();
        std::memcpy( p, initialData, size );
        this->unmap();
    }
}


void* StagingBuffer::map()
{
    void* p;
    check( vkMapMemory(
        ctx->dev,
        this->memory,
        0,                  //offset
        this->byteSize,
        0,                  //flags
        &(p)
    ));
    return p;
}

void StagingBuffer::unmap()
{
    vkUnmapMemory(
        ctx->dev,
        this->memory
    );

    //https://stackoverflow.com/questions/48667439/should-i-syncronize-an-access-to-a-memory-with-host-visible-bit-host-coherent
    auto cmd = CommandBuffer::beginImmediateCommands();
    Buffers::memoryBarrier(cmd,this->buffer);
    CommandBuffer::endImmediateCommands(cmd);
}


void StagingBuffer::cleanup()
{
    Buffer::cleanup();
}

DeviceLocalBuffer::DeviceLocalBuffer( VulkanContext* ctx_, const void* initialData,VkDeviceSize size,
                        VkBufferUsageFlags usage, const std::string& name_)
    : Buffer(ctx_,
             usage|VK_BUFFER_USAGE_TRANSFER_SRC_BIT|VK_BUFFER_USAGE_TRANSFER_DST_BIT,
             size,
             name_)
{
    this->memory = DeviceLocalBuffer::allocateMemory(this->ctx,
        this->memoryRequirements.memoryTypeBits,
        std::max(this->memoryRequirements.size,size), "memory for "+name);
    this->bindMemory(this->memory,0,true);

    if(initialData != nullptr ){
        StagingBuffer* staging = new StagingBuffer(ctx, initialData, size, "temporary staging buffer for "+name );
        staging->copyTo(this);
        staging->cleanup();
        delete staging;
    }

}


DeviceLocalBuffer::DeviceLocalBuffer( VulkanContext* ctx_, VkDeviceMemory memory_, VkDeviceSize offset,
                    VkDeviceSize size, VkBufferUsageFlags usage, const std::string& name_)
    : Buffer(
             ctx_,
             usage|VK_BUFFER_USAGE_TRANSFER_SRC_BIT|VK_BUFFER_USAGE_TRANSFER_DST_BIT,
             size,
             name_)
{
    this->bindMemory(memory_,offset,false);
}

VkDeviceMemory DeviceLocalBuffer::allocateMemory(VulkanContext* ctx,
        std::uint32_t memoryTypeBits, VkDeviceSize size, std::string name)
{
    auto properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    return Buffers::allocateMemory(ctx,memoryTypeBits,size,properties,name);
}

void DeviceLocalBuffer::cleanup()
{
    Buffer::cleanup();
}


namespace Buffers{

VkDeviceMemory allocateMemory(
    VulkanContext* ctx,
    std::uint32_t memoryTypeBits,
    VkDeviceSize size,
    VkMemoryPropertyFlags properties,
    const std::string& name)
{
    //properties is usually either HOST_VISIBLE | HOST_COHERENT
    //           or else it's DEVICE_LOCAL

    //Get properties of the various memory types the GPU has
    //This returns a list of memory types. Each memory type
    //has propertyFlags and a heapIndex. The propertyFlags
    //is a bitwise OR of DEVICE_LOCAL_BIT, HOST_VISIBLE_BIT, etc.
    VkPhysicalDeviceMemoryProperties memprops;
    vkGetPhysicalDeviceMemoryProperties(
        ctx->physdev,
        &(memprops)
    );

    bool ok=false;

    //look at each memory type...
    unsigned i;
    for(i=0;i<memprops.memoryTypeCount;++i){

        //if this is not one of the types that
        //the buffer permits, then skip it
        if( !( (1<<i) & memoryTypeBits ) )
            continue;

        //if type i meets all the requested property bits,
        //we can choose it
        auto masked = properties & memprops.memoryTypes[i].propertyFlags;
        if(properties == masked){
            ok=true;
            break;
        }
    }

    if(!ok)
        throw std::runtime_error("No memory with desired type & properties");


    VkDeviceMemory memory;
    check( vkAllocateMemory(
        ctx->dev,
        VkMemoryAllocateInfo{
            .sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .pNext=nullptr,
            .allocationSize=size,
            .memoryTypeIndex=i
        },
        nullptr,
        &(memory)
    ));
    ctx->setObjectName(memory,name);
    return memory;
}


void memoryBarrier(VkCommandBuffer cmd, VkBuffer buffer)
{
    vkCmdPipelineBarrier(
        cmd,
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,      //source stage mask
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,      //destination stage mask
        0,      //dependency flags
        1,
        VkMemoryBarrier{
            .sType=VK_STRUCTURE_TYPE_MEMORY_BARRIER,
            .pNext=nullptr,
            .srcAccessMask=VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT,
            .dstAccessMask=VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT
        },
        1,

        VkBufferMemoryBarrier{
            .sType=VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
            .pNext=nullptr,
            .srcAccessMask=VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT,
            .dstAccessMask=VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT,
            .srcQueueFamilyIndex=VK_QUEUE_FAMILY_IGNORED,
            .dstQueueFamilyIndex=VK_QUEUE_FAMILY_IGNORED,
            .buffer=buffer,
            .offset=0,
            .size=VK_WHOLE_SIZE
        },
        0,      //image memory barriers
        VkImageMemoryBarrier{}
    );
}

}; //namespace
