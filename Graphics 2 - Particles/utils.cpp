#include "utils.h"
#include <tuple>
#include "CommandBuffer.h"
#include "GraphicsPipeline.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include "CleanupManager.h"

static std::vector<std::function<void(unsigned)> > frameCompleteCallbacks;
static std::vector<std::function<void(int,VkCommandBuffer)> > frameBeginCallbacks;
static std::vector<std::function<void(int,VkCommandBuffer)> > frameEndCallbacks;

//eventually, this wraps, but that's not a problem since we shouldn't have
//4 billion frames outstanding anyway
//This gets incremented at the end of endFrame in preparation for the next frame.
//This also means that anything set up before rendering begins
//is associated with frame 0
static unsigned currentFrameIdentifier=0;

static std::vector<VkFence> availableFences;

//first=frame number, second=fence
static std::vector< std::pair<unsigned,VkFence> > activeFences;

static bool inFrame=false;

static int currentSwapchainIndex=-1;
static VkCommandBuffer currentCommandBuffer=VK_NULL_HANDLE;

namespace utils{


VkCommandBuffer beginFrame(VulkanContext* ctx)
{

    //deal with any signaled fences from past frames
    for( auto it = activeFences.begin(); it != activeFences.end() ; ){
        auto fstat = vkGetFenceStatus(ctx->dev, it->second);
        if( fstat == VK_SUCCESS ){
            //this frame is done; notify components that they can
            //reclaim resources
            availableFences.push_back(it->second);
            vkResetFences(ctx->dev,1,&it->second);
            for(auto& f : frameCompleteCallbacks ){
                f(it->first);       //tell them the frame number
            }
            it = activeFences.erase(it);
        } else if( fstat == VK_NOT_READY ){
            //frame not yet done; look at next fence
            it++;
        } else if( fstat == VK_ERROR_DEVICE_LOST ){
            throw std::runtime_error("Device was lost");
        }
    }


    if(inFrame ){
        throw std::runtime_error("beginFrame() called twice with no intervening endFrame()");
    }
    inFrame=true;

    std::uint32_t imageindex;
    vkAcquireNextImageKHR(
        ctx->dev,
        ctx->swapchain,
        0xffffffffffffffff,
        ctx->imageAcquiredSemaphore,
        nullptr,
        &(imageindex)
    );

    currentSwapchainIndex = (int)imageindex;

    auto cmd = CommandBuffer::allocate();
    currentCommandBuffer = cmd;

    check(vkBeginCommandBuffer(
        cmd,
        VkCommandBufferBeginInfo{
            .sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .pNext=nullptr,
            .flags=0,
            .pInheritanceInfo=nullptr
        }
    ));

    for(auto& f : frameBeginCallbacks ){
        f(currentSwapchainIndex,currentCommandBuffer);
    }

    return currentCommandBuffer;
}


void endFrame(VulkanContext* ctx)
{
    if(!inFrame){
        throw std::runtime_error("endFrame called without matching beginFrame");
    }


    for(auto& f : frameEndCallbacks ){
        f(currentSwapchainIndex,currentCommandBuffer);
    }

    check(vkEndCommandBuffer(currentCommandBuffer));


   if( availableFences.empty() ){
        VkFenceCreateInfo ci{
            .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0          //create as unsignaled
        };
        VkFence f;
        check(vkCreateFence(ctx->dev, &ci, nullptr, &f ));
        activeFences.push_back( std::make_pair(currentFrameIdentifier, f ) );
        CleanupManager::registerCleanupFunction( [f,ctx](){
            vkDestroyFence(ctx->dev,f,nullptr);
        });
    } else {
        VkFence f = availableFences.back();
        availableFences.pop_back();
        activeFences.push_back( std::make_pair(currentFrameIdentifier, f ) );
    }


    VkPipelineStageFlags waitDestStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    check(vkQueueSubmit(
        ctx->graphicsQueue,
        1,
        VkSubmitInfo{
            .sType=VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .pNext=nullptr,
            .waitSemaphoreCount=1,
            .pWaitSemaphores=&ctx->imageAcquiredSemaphore,
            .pWaitDstStageMask = &waitDestStageMask,
            .commandBufferCount=1,
            .pCommandBuffers = &currentCommandBuffer,
            .signalSemaphoreCount=1,
            .pSignalSemaphores=&ctx->renderCompleteSemaphore
        },
        activeFences.back().second         //always the last one in the list
    ));

    std::uint32_t ii = (std::uint32_t)currentSwapchainIndex;
    check(vkQueuePresentKHR(
        ctx->presentQueue,
        VkPresentInfoKHR{
            .sType=VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
            .pNext=nullptr,
            .waitSemaphoreCount=1,
            .pWaitSemaphores = &ctx->renderCompleteSemaphore,
            .swapchainCount=1,
            .pSwapchains = &ctx->swapchain,
            .pImageIndices=&ii,
            .pResults=nullptr
        }
    ));

    //FIXME: Remove this wait and then dispose of command buffer
    //when frame is complete. Also make several renderCompleteSemaphore's above.
    check(vkQueueWaitIdle(ctx->presentQueue));

    CommandBuffer::dispose(currentCommandBuffer);

    ++currentFrameIdentifier;

    inFrame=false;
    currentSwapchainIndex=-1;
    currentCommandBuffer = VK_NULL_HANDLE;

}


int computePadding(VkDeviceSize offset, VkDeviceSize alignment )
{
    VkDeviceSize extra = offset  % alignment;
    if(extra == 0)
        return 0;
    VkDeviceSize padding = alignment-extra;
    return (int)padding;
}

std::vector<char> readFile(std::string filename)
{
    std::ifstream in(filename,std::ios::binary);
    if(!in.good()){
        throw std::runtime_error("Cannot read file "+filename);
    }
    in.seekg(0,std::ios::end);
    auto size = in.tellg();
    in.seekg(0);
    std::vector<char> d;
    d.resize(size);
    in.read(d.data(),size);
    return d;
}

void registerFrameCompleteCallback( std::function<void(unsigned)> f){
    frameCompleteCallbacks.push_back(f);
}


void registerFrameBeginCallback( std::function<void(int,VkCommandBuffer)> f){
    frameBeginCallbacks.push_back(f);
}


void registerFrameEndCallback( std::function<void(int,VkCommandBuffer)> f){
    frameEndCallbacks.push_back(f);
}

unsigned getCurrentFrameIdentifier()
{
    if(!inFrame)
        throw std::runtime_error("Cannot call getCurrentFrameIdentifier() outside of a render operation");
    return currentFrameIdentifier;
}

int getSwapchainImageIndex()
{
    if(!inFrame)
        throw std::runtime_error("Cannot call getSwapchainImageIndex() outside of a render operation");
    return currentSwapchainIndex;
}

};  //end namespace

