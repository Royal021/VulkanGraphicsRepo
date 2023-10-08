#include "CommandBuffer.h"
#include "CleanupManager.h"

static VulkanContext* ctx;
static VkCommandPool pool;

namespace CommandBuffer{

bool initialized()
{
    return ctx != nullptr;
}

void initialize(VulkanContext* ctx_)
{
    if(initialized())
        return;

    ctx=ctx_;
    check(vkCreateCommandPool(
        ctx->dev,
        VkCommandPoolCreateInfo{
            .sType=VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .pNext=nullptr,
            .flags=VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
            .queueFamilyIndex = ctx->graphicsQueueIndex
        },
        nullptr,
        &(pool)
    ));

    CleanupManager::registerCleanupFunction([](){
        vkDestroyCommandPool(
            ctx->dev,
            pool,
            nullptr
        );
    });
}

VkCommandBuffer allocate()
{
    VkCommandBuffer cmd;
    check(vkAllocateCommandBuffers(
        ctx->dev,
        VkCommandBufferAllocateInfo{
            .sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .pNext=nullptr,
            .commandPool=pool,
            .level=VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            .commandBufferCount=1
        },
        &(cmd)
    ));
    return cmd;
}

void dispose(VkCommandBuffer cmd)
{
    vkFreeCommandBuffers(
        ctx->dev,
        pool,
        1,
        &cmd
    );
}


VkCommandBuffer beginImmediateCommands()
{
    vkQueueWaitIdle(ctx->graphicsQueue);
    auto cmd = allocate();
    check( vkBeginCommandBuffer(
        cmd,
        VkCommandBufferBeginInfo{
            .sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .pNext=nullptr,
            .flags=VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
            .pInheritanceInfo=nullptr
        }
    ));
    return cmd;
}

void endImmediateCommands(VkCommandBuffer cmd)
{
    vkEndCommandBuffer(cmd);
    check(vkQueueSubmit(
        ctx->graphicsQueue,
        1,
        VkSubmitInfo{
            .sType=VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .pNext=nullptr,
            .waitSemaphoreCount=0,
            .pWaitSemaphores=nullptr,
            .pWaitDstStageMask=nullptr,
            .commandBufferCount=1,
            .pCommandBuffers=&cmd,
            .signalSemaphoreCount=0,
            .pSignalSemaphores=nullptr
        },
        nullptr
    ));
    vkQueueWaitIdle(ctx->graphicsQueue);
    dispose(cmd);
}

}; //namespace



