//Generated from vk.xml, which has this copyright:
// 
// Copyright 2015-2022 The Khronos Group Inc.
// 
// SPDX-License-Identifier: Apache-2.0 OR MIT
// 

#include "vk.h"
#include <SDL_vulkan.h>
#include <stdexcept>
#include <exception>
#include <iostream>

static void notLoaded(){
    std::cerr << "This Vulkan function is not available\n";
    std::terminate();
}

static void _needLoad()
{
    throw std::runtime_error("The Vulkan functions have not been loaded.");
}

static void* loadVulkanFunction(VkInstance instance, const char* name)
{
    static PFN_vkGetInstanceProcAddr vGetProcAddr;
    if(!vGetProcAddr){
        vGetProcAddr = (PFN_vkGetInstanceProcAddr) SDL_Vulkan_GetVkGetInstanceProcAddr();
        if(!vGetProcAddr){
            throw std::runtime_error("Cannot get vkGetInstanceProcAddr() pointer");
        }
    }
    void* tmp = (void*) (vGetProcAddr(instance,name));
    if(tmp)
        return tmp;
    else
        return (void*)notLoaded;
}
static PFN_vkGetImageSubresourceLayout _impl_vkGetImageSubresourceLayout;
void vkGetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* 
        pSubresource, VkSubresourceLayout* pLayout ){
  if(!_impl_vkGetImageSubresourceLayout) _needLoad(); 
  _impl_vkGetImageSubresourceLayout(device,image,pSubresource,pLayout);
}
static PFN_vkDestroyImage _impl_vkDestroyImage;
void vkDestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroyImage) _needLoad(); 
  _impl_vkDestroyImage(device,image,pAllocator);
}
static PFN_vkSetDebugUtilsObjectTagEXT _impl_vkSetDebugUtilsObjectTagEXT;
VkResult vkSetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* 
        pTagInfo ){
  if(!_impl_vkSetDebugUtilsObjectTagEXT) _needLoad(); 
  return _impl_vkSetDebugUtilsObjectTagEXT(device,pTagInfo);
}
static PFN_vkSubmitDebugUtilsMessageEXT _impl_vkSubmitDebugUtilsMessageEXT;
void vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT 
        messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* 
        pCallbackData ){
  if(!_impl_vkSubmitDebugUtilsMessageEXT) _needLoad(); 
  _impl_vkSubmitDebugUtilsMessageEXT(instance,messageSeverity,messageTypes,pCallbackData);
}
static PFN_vkCmdDraw _impl_vkCmdDraw;
void vkCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, 
        uint32_t firstVertex, uint32_t firstInstance ){
  if(!_impl_vkCmdDraw) _needLoad(); 
  _impl_vkCmdDraw(commandBuffer,vertexCount,instanceCount,firstVertex,firstInstance);
}
static PFN_vkGetFenceStatus _impl_vkGetFenceStatus;
VkResult vkGetFenceStatus(VkDevice device, VkFence fence ){
  if(!_impl_vkGetFenceStatus) _needLoad(); 
  return _impl_vkGetFenceStatus(device,fence);
}
static PFN_vkCreateCommandPool _impl_vkCreateCommandPool;
VkResult vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool ){
  if(!_impl_vkCreateCommandPool) _needLoad(); 
  return _impl_vkCreateCommandPool(device,pCreateInfo,pAllocator,pCommandPool);
}
static PFN_vkGetImageMemoryRequirements _impl_vkGetImageMemoryRequirements;
void vkGetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* 
        pMemoryRequirements ){
  if(!_impl_vkGetImageMemoryRequirements) _needLoad(); 
  _impl_vkGetImageMemoryRequirements(device,image,pMemoryRequirements);
}
static PFN_vkCmdWaitEvents _impl_vkCmdWaitEvents;
void vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* 
        pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, 
        uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t 
        bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, 
        uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers 
        ){
  if(!_impl_vkCmdWaitEvents) _needLoad(); 
  _impl_vkCmdWaitEvents(commandBuffer,eventCount,pEvents,srcStageMask,dstStageMask,memoryBarrierCount,pMemoryBarriers,bufferMemoryBarrierCount,pBufferMemoryBarriers,imageMemoryBarrierCount,pImageMemoryBarriers);
}
static PFN_vkCmdSetLineWidth _impl_vkCmdSetLineWidth;
void vkCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth ){
  if(!_impl_vkCmdSetLineWidth) _needLoad(); 
  _impl_vkCmdSetLineWidth(commandBuffer,lineWidth);
}
static PFN_vkGetRenderAreaGranularity _impl_vkGetRenderAreaGranularity;
void vkGetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* 
        pGranularity ){
  if(!_impl_vkGetRenderAreaGranularity) _needLoad(); 
  _impl_vkGetRenderAreaGranularity(device,renderPass,pGranularity);
}
static PFN_vkCreateImage _impl_vkCreateImage;
VkResult vkCreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkImage* pImage ){
  if(!_impl_vkCreateImage) _needLoad(); 
  return _impl_vkCreateImage(device,pCreateInfo,pAllocator,pImage);
}
static PFN_vkCmdBeginDebugUtilsLabelEXT _impl_vkCmdBeginDebugUtilsLabelEXT;
void vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* 
        pLabelInfo ){
  if(!_impl_vkCmdBeginDebugUtilsLabelEXT) _needLoad(); 
  _impl_vkCmdBeginDebugUtilsLabelEXT(commandBuffer,pLabelInfo);
}
static PFN_vkCreateDevice _impl_vkCreateDevice;
VkResult vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice ){
  if(!_impl_vkCreateDevice) _needLoad(); 
  return _impl_vkCreateDevice(physicalDevice,pCreateInfo,pAllocator,pDevice);
}
static PFN_vkAllocateMemory _impl_vkAllocateMemory;
VkResult vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, 
        const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory ){
  if(!_impl_vkAllocateMemory) _needLoad(); 
  return _impl_vkAllocateMemory(device,pAllocateInfo,pAllocator,pMemory);
}
static PFN_vkCreateSwapchainKHR _impl_vkCreateSwapchainKHR;
VkResult vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain ){
  if(!_impl_vkCreateSwapchainKHR) _needLoad(); 
  return _impl_vkCreateSwapchainKHR(device,pCreateInfo,pAllocator,pSwapchain);
}
static PFN_vkDestroyRenderPass _impl_vkDestroyRenderPass;
void vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroyRenderPass) _needLoad(); 
  _impl_vkDestroyRenderPass(device,renderPass,pAllocator);
}
static PFN_vkCmdSetStencilReference _impl_vkCmdSetStencilReference;
void vkCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, 
        uint32_t reference ){
  if(!_impl_vkCmdSetStencilReference) _needLoad(); 
  _impl_vkCmdSetStencilReference(commandBuffer,faceMask,reference);
}
static PFN_vkQueueWaitIdle _impl_vkQueueWaitIdle;
VkResult vkQueueWaitIdle(VkQueue queue ){
  if(!_impl_vkQueueWaitIdle) _needLoad(); 
  return _impl_vkQueueWaitIdle(queue);
}
static PFN_vkCmdBeginRenderPass _impl_vkCmdBeginRenderPass;
void vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* 
        pRenderPassBegin, VkSubpassContents contents ){
  if(!_impl_vkCmdBeginRenderPass) _needLoad(); 
  _impl_vkCmdBeginRenderPass(commandBuffer,pRenderPassBegin,contents);
}
static PFN_vkGetEventStatus _impl_vkGetEventStatus;
VkResult vkGetEventStatus(VkDevice device, VkEvent event ){
  if(!_impl_vkGetEventStatus) _needLoad(); 
  return _impl_vkGetEventStatus(device,event);
}
static PFN_vkCmdSetStencilCompareMask _impl_vkCmdSetStencilCompareMask;
void vkCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags 
        faceMask, uint32_t compareMask ){
  if(!_impl_vkCmdSetStencilCompareMask) _needLoad(); 
  _impl_vkCmdSetStencilCompareMask(commandBuffer,faceMask,compareMask);
}
static PFN_vkCmdDrawIndexedIndirect _impl_vkCmdDrawIndexedIndirect;
void vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize 
        offset, uint32_t drawCount, uint32_t stride ){
  if(!_impl_vkCmdDrawIndexedIndirect) _needLoad(); 
  _impl_vkCmdDrawIndexedIndirect(commandBuffer,buffer,offset,drawCount,stride);
}
static PFN_vkDestroyDebugUtilsMessengerEXT _impl_vkDestroyDebugUtilsMessengerEXT;
void vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT 
        messenger, const VkAllocationCallbacks* pAllocator ){
  if(!_impl_vkDestroyDebugUtilsMessengerEXT) _needLoad(); 
  _impl_vkDestroyDebugUtilsMessengerEXT(instance,messenger,pAllocator);
}
static PFN_vkCreateBuffer _impl_vkCreateBuffer;
VkResult vkCreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer ){
  if(!_impl_vkCreateBuffer) _needLoad(); 
  return _impl_vkCreateBuffer(device,pCreateInfo,pAllocator,pBuffer);
}
static PFN_vkCreateDebugUtilsMessengerEXT _impl_vkCreateDebugUtilsMessengerEXT;
VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* 
        pMessenger ){
  if(!_impl_vkCreateDebugUtilsMessengerEXT) _needLoad(); 
  return _impl_vkCreateDebugUtilsMessengerEXT(instance,pCreateInfo,pAllocator,pMessenger);
}
static PFN_vkCmdCopyBuffer _impl_vkCmdCopyBuffer;
void vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer 
        dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions ){
  if(!_impl_vkCmdCopyBuffer) _needLoad(); 
  _impl_vkCmdCopyBuffer(commandBuffer,srcBuffer,dstBuffer,regionCount,pRegions);
}
static PFN_vkCmdUpdateBuffer _impl_vkCmdUpdateBuffer;
void vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize 
        dstOffset, VkDeviceSize dataSize, const void* pData ){
  if(!_impl_vkCmdUpdateBuffer) _needLoad(); 
  _impl_vkCmdUpdateBuffer(commandBuffer,dstBuffer,dstOffset,dataSize,pData);
}
static PFN_vkEndCommandBuffer _impl_vkEndCommandBuffer;
VkResult vkEndCommandBuffer(VkCommandBuffer commandBuffer ){
  if(!_impl_vkEndCommandBuffer) _needLoad(); 
  return _impl_vkEndCommandBuffer(commandBuffer);
}
static PFN_vkResetCommandBuffer _impl_vkResetCommandBuffer;
VkResult vkResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags 
        flags ){
  if(!_impl_vkResetCommandBuffer) _needLoad(); 
  return _impl_vkResetCommandBuffer(commandBuffer,flags);
}
static PFN_vkCmdCopyQueryPoolResults _impl_vkCmdCopyQueryPoolResults;
void vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, 
        uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize 
        dstOffset, VkDeviceSize stride, VkQueryResultFlags flags ){
  if(!_impl_vkCmdCopyQueryPoolResults) _needLoad(); 
  _impl_vkCmdCopyQueryPoolResults(commandBuffer,queryPool,firstQuery,queryCount,dstBuffer,dstOffset,stride,flags);
}
static PFN_vkGetPhysicalDeviceFormatProperties _impl_vkGetPhysicalDeviceFormatProperties;
void vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat 
        format, VkFormatProperties* pFormatProperties ){
  if(!_impl_vkGetPhysicalDeviceFormatProperties) _needLoad(); 
  _impl_vkGetPhysicalDeviceFormatProperties(physicalDevice,format,pFormatProperties);
}
static PFN_vkGetPhysicalDeviceFeatures _impl_vkGetPhysicalDeviceFeatures;
void vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* 
        pFeatures ){
  if(!_impl_vkGetPhysicalDeviceFeatures) _needLoad(); 
  _impl_vkGetPhysicalDeviceFeatures(physicalDevice,pFeatures);
}
static PFN_vkQueueSubmit _impl_vkQueueSubmit;
VkResult vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, 
        VkFence fence ){
  if(!_impl_vkQueueSubmit) _needLoad(); 
  return _impl_vkQueueSubmit(queue,submitCount,pSubmits,fence);
}
static PFN_vkCreateGraphicsPipelines _impl_vkCreateGraphicsPipelines;
VkResult vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, 
        const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines ){
  if(!_impl_vkCreateGraphicsPipelines) _needLoad(); 
  return _impl_vkCreateGraphicsPipelines(device,pipelineCache,createInfoCount,pCreateInfos,pAllocator,pPipelines);
}
static PFN_vkGetPhysicalDeviceMemoryProperties _impl_vkGetPhysicalDeviceMemoryProperties;
void vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* 
        pMemoryProperties ){
  if(!_impl_vkGetPhysicalDeviceMemoryProperties) _needLoad(); 
  _impl_vkGetPhysicalDeviceMemoryProperties(physicalDevice,pMemoryProperties);
}
static PFN_vkGetPhysicalDeviceSparseImageFormatProperties _impl_vkGetPhysicalDeviceSparseImageFormatProperties;
void vkGetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, 
        VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags 
        usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* 
        pProperties ){
  if(!_impl_vkGetPhysicalDeviceSparseImageFormatProperties) _needLoad(); 
  _impl_vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice,format,type,samples,usage,tiling,pPropertyCount,pProperties);
}
static PFN_vkCmdClearDepthStencilImage _impl_vkCmdClearDepthStencilImage;
void vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, 
        const VkImageSubresourceRange* pRanges ){
  if(!_impl_vkCmdClearDepthStencilImage) _needLoad(); 
  _impl_vkCmdClearDepthStencilImage(commandBuffer,image,imageLayout,pDepthStencil,rangeCount,pRanges);
}
static PFN_vkCmdFillBuffer _impl_vkCmdFillBuffer;
void vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize 
        dstOffset, VkDeviceSize size, uint32_t data ){
  if(!_impl_vkCmdFillBuffer) _needLoad(); 
  _impl_vkCmdFillBuffer(commandBuffer,dstBuffer,dstOffset,size,data);
}
static PFN_vkBeginCommandBuffer _impl_vkBeginCommandBuffer;
VkResult vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* 
        pBeginInfo ){
  if(!_impl_vkBeginCommandBuffer) _needLoad(); 
  return _impl_vkBeginCommandBuffer(commandBuffer,pBeginInfo);
}
static PFN_vkCmdPipelineBarrier _impl_vkCmdPipelineBarrier;
void vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, 
        VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t 
        memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, 
        const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, 
        const VkImageMemoryBarrier* pImageMemoryBarriers ){
  if(!_impl_vkCmdPipelineBarrier) _needLoad(); 
  _impl_vkCmdPipelineBarrier(commandBuffer,srcStageMask,dstStageMask,dependencyFlags,memoryBarrierCount,pMemoryBarriers,bufferMemoryBarrierCount,pBufferMemoryBarriers,imageMemoryBarrierCount,pImageMemoryBarriers);
}
static PFN_vkFreeMemory _impl_vkFreeMemory;
void vkFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkFreeMemory) _needLoad(); 
  _impl_vkFreeMemory(device,memory,pAllocator);
}
static PFN_vkCmdEndDebugUtilsLabelEXT _impl_vkCmdEndDebugUtilsLabelEXT;
void vkCmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer ){
  if(!_impl_vkCmdEndDebugUtilsLabelEXT) _needLoad(); 
  _impl_vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}
static PFN_vkUnmapMemory _impl_vkUnmapMemory;
void vkUnmapMemory(VkDevice device, VkDeviceMemory memory ){
  if(!_impl_vkUnmapMemory) _needLoad(); 
  _impl_vkUnmapMemory(device,memory);
}
static PFN_vkCreateEvent _impl_vkCreateEvent;
VkResult vkCreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkEvent* pEvent ){
  if(!_impl_vkCreateEvent) _needLoad(); 
  return _impl_vkCreateEvent(device,pCreateInfo,pAllocator,pEvent);
}
static PFN_vkCmdCopyImage _impl_vkCmdCopyImage;
void vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const VkImageCopy* pRegions ){
  if(!_impl_vkCmdCopyImage) _needLoad(); 
  _impl_vkCmdCopyImage(commandBuffer,srcImage,srcImageLayout,dstImage,dstImageLayout,regionCount,pRegions);
}
static PFN_vkDestroyDescriptorSetLayout _impl_vkDestroyDescriptorSetLayout;
void vkDestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, 
        const VkAllocationCallbacks* pAllocator ){
  if(!_impl_vkDestroyDescriptorSetLayout) _needLoad(); 
  _impl_vkDestroyDescriptorSetLayout(device,descriptorSetLayout,pAllocator);
}
static PFN_vkDestroyQueryPool _impl_vkDestroyQueryPool;
void vkDestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroyQueryPool) _needLoad(); 
  _impl_vkDestroyQueryPool(device,queryPool,pAllocator);
}
static PFN_vkEnumeratePhysicalDevices _impl_vkEnumeratePhysicalDevices;
VkResult vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, 
        VkPhysicalDevice* pPhysicalDevices ){
  if(!_impl_vkEnumeratePhysicalDevices) _needLoad(); 
  return _impl_vkEnumeratePhysicalDevices(instance,pPhysicalDeviceCount,pPhysicalDevices);
}
static PFN_vkCmdClearColorImage _impl_vkCmdClearColorImage;
void vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const 
        VkImageSubresourceRange* pRanges ){
  if(!_impl_vkCmdClearColorImage) _needLoad(); 
  _impl_vkCmdClearColorImage(commandBuffer,image,imageLayout,pColor,rangeCount,pRanges);
}
static PFN_vkEnumerateInstanceExtensionProperties _impl_vkEnumerateInstanceExtensionProperties;
VkResult vkEnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* 
        pPropertyCount, VkExtensionProperties* pProperties ){
  if(!_impl_vkEnumerateInstanceExtensionProperties) _needLoad(); 
  return _impl_vkEnumerateInstanceExtensionProperties(pLayerName,pPropertyCount,pProperties);
}
static PFN_vkWaitForFences _impl_vkWaitForFences;
VkResult vkWaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, 
        VkBool32 waitAll, uint64_t timeout ){
  if(!_impl_vkWaitForFences) _needLoad(); 
  return _impl_vkWaitForFences(device,fenceCount,pFences,waitAll,timeout);
}
static PFN_vkDestroyFramebuffer _impl_vkDestroyFramebuffer;
void vkDestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroyFramebuffer) _needLoad(); 
  _impl_vkDestroyFramebuffer(device,framebuffer,pAllocator);
}
static PFN_vkEnumerateDeviceLayerProperties _impl_vkEnumerateDeviceLayerProperties;
VkResult vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* 
        pPropertyCount, VkLayerProperties* pProperties ){
  if(!_impl_vkEnumerateDeviceLayerProperties) _needLoad(); 
  return _impl_vkEnumerateDeviceLayerProperties(physicalDevice,pPropertyCount,pProperties);
}
static PFN_vkCmdBeginQuery _impl_vkCmdBeginQuery;
void vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t 
        query, VkQueryControlFlags flags ){
  if(!_impl_vkCmdBeginQuery) _needLoad(); 
  _impl_vkCmdBeginQuery(commandBuffer,queryPool,query,flags);
}
static PFN_vkDestroyDevice _impl_vkDestroyDevice;
void vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator ){
  if(!_impl_vkDestroyDevice) _needLoad(); 
  _impl_vkDestroyDevice(device,pAllocator);
}
static PFN_vkGetSwapchainImagesKHR _impl_vkGetSwapchainImagesKHR;
VkResult vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* 
        pSwapchainImageCount, VkImage* pSwapchainImages ){
  if(!_impl_vkGetSwapchainImagesKHR) _needLoad(); 
  return _impl_vkGetSwapchainImagesKHR(device,swapchain,pSwapchainImageCount,pSwapchainImages);
}
static PFN_vkDestroyPipeline _impl_vkDestroyPipeline;
void vkDestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroyPipeline) _needLoad(); 
  _impl_vkDestroyPipeline(device,pipeline,pAllocator);
}
static PFN_vkSetDebugUtilsObjectNameEXT _impl_vkSetDebugUtilsObjectNameEXT;
VkResult vkSetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* 
        pNameInfo ){
  if(!_impl_vkSetDebugUtilsObjectNameEXT) _needLoad(); 
  return _impl_vkSetDebugUtilsObjectNameEXT(device,pNameInfo);
}
static PFN_vkGetPhysicalDeviceProperties _impl_vkGetPhysicalDeviceProperties;
void vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* 
        pProperties ){
  if(!_impl_vkGetPhysicalDeviceProperties) _needLoad(); 
  _impl_vkGetPhysicalDeviceProperties(physicalDevice,pProperties);
}
static PFN_vkDestroyPipelineLayout _impl_vkDestroyPipelineLayout;
void vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const 
        VkAllocationCallbacks* pAllocator ){
  if(!_impl_vkDestroyPipelineLayout) _needLoad(); 
  _impl_vkDestroyPipelineLayout(device,pipelineLayout,pAllocator);
}
static PFN_vkCmdDispatch _impl_vkCmdDispatch;
void vkCmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t 
        groupCountY, uint32_t groupCountZ ){
  if(!_impl_vkCmdDispatch) _needLoad(); 
  _impl_vkCmdDispatch(commandBuffer,groupCountX,groupCountY,groupCountZ);
}
static PFN_vkGetPhysicalDeviceSurfaceSupportKHR _impl_vkGetPhysicalDeviceSurfaceSupportKHR;
VkResult vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t 
        queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported ){
  if(!_impl_vkGetPhysicalDeviceSurfaceSupportKHR) _needLoad(); 
  return _impl_vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice,queueFamilyIndex,surface,pSupported);
}
static PFN_vkCmdSetViewport _impl_vkCmdSetViewport;
void vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t 
        viewportCount, const VkViewport* pViewports ){
  if(!_impl_vkCmdSetViewport) _needLoad(); 
  _impl_vkCmdSetViewport(commandBuffer,firstViewport,viewportCount,pViewports);
}
static PFN_vkCmdBindIndexBuffer _impl_vkCmdBindIndexBuffer;
void vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize 
        offset, VkIndexType indexType ){
  if(!_impl_vkCmdBindIndexBuffer) _needLoad(); 
  _impl_vkCmdBindIndexBuffer(commandBuffer,buffer,offset,indexType);
}
static PFN_vkFreeCommandBuffers _impl_vkFreeCommandBuffers;
void vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, 
        const VkCommandBuffer* pCommandBuffers ){
  if(!_impl_vkFreeCommandBuffers) _needLoad(); 
  _impl_vkFreeCommandBuffers(device,commandPool,commandBufferCount,pCommandBuffers);
}
static PFN_vkGetDeviceMemoryCommitment _impl_vkGetDeviceMemoryCommitment;
void vkGetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* 
        pCommittedMemoryInBytes ){
  if(!_impl_vkGetDeviceMemoryCommitment) _needLoad(); 
  _impl_vkGetDeviceMemoryCommitment(device,memory,pCommittedMemoryInBytes);
}
static PFN_vkCreateQueryPool _impl_vkCreateQueryPool;
VkResult vkCreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool ){
  if(!_impl_vkCreateQueryPool) _needLoad(); 
  return _impl_vkCreateQueryPool(device,pCreateInfo,pAllocator,pQueryPool);
}
static PFN_vkGetPipelineCacheData _impl_vkGetPipelineCacheData;
VkResult vkGetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* 
        pDataSize, void* pData ){
  if(!_impl_vkGetPipelineCacheData) _needLoad(); 
  return _impl_vkGetPipelineCacheData(device,pipelineCache,pDataSize,pData);
}
static PFN_vkDestroyImageView _impl_vkDestroyImageView;
void vkDestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroyImageView) _needLoad(); 
  _impl_vkDestroyImageView(device,imageView,pAllocator);
}
static PFN_vkCreateShaderModule _impl_vkCreateShaderModule;
VkResult vkCreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule ){
  if(!_impl_vkCreateShaderModule) _needLoad(); 
  return _impl_vkCreateShaderModule(device,pCreateInfo,pAllocator,pShaderModule);
}
static PFN_vkDestroyDescriptorPool _impl_vkDestroyDescriptorPool;
void vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const 
        VkAllocationCallbacks* pAllocator ){
  if(!_impl_vkDestroyDescriptorPool) _needLoad(); 
  _impl_vkDestroyDescriptorPool(device,descriptorPool,pAllocator);
}
static PFN_vkCreateFramebuffer _impl_vkCreateFramebuffer;
VkResult vkCreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer ){
  if(!_impl_vkCreateFramebuffer) _needLoad(); 
  return _impl_vkCreateFramebuffer(device,pCreateInfo,pAllocator,pFramebuffer);
}
static PFN_vkQueueInsertDebugUtilsLabelEXT _impl_vkQueueInsertDebugUtilsLabelEXT;
void vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo 
        ){
  if(!_impl_vkQueueInsertDebugUtilsLabelEXT) _needLoad(); 
  _impl_vkQueueInsertDebugUtilsLabelEXT(queue,pLabelInfo);
}
static PFN_vkCmdResetEvent _impl_vkCmdResetEvent;
void vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags 
        stageMask ){
  if(!_impl_vkCmdResetEvent) _needLoad(); 
  _impl_vkCmdResetEvent(commandBuffer,event,stageMask);
}
static PFN_vkCmdSetDepthBias _impl_vkCmdSetDepthBias;
void vkCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, 
        float depthBiasClamp, float depthBiasSlopeFactor ){
  if(!_impl_vkCmdSetDepthBias) _needLoad(); 
  _impl_vkCmdSetDepthBias(commandBuffer,depthBiasConstantFactor,depthBiasClamp,depthBiasSlopeFactor);
}
static PFN_vkMapMemory _impl_vkMapMemory;
VkResult vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, 
        VkDeviceSize size, VkMemoryMapFlags flags, void** ppData ){
  if(!_impl_vkMapMemory) _needLoad(); 
  return _impl_vkMapMemory(device,memory,offset,size,flags,ppData);
}
static PFN_vkGetImageSparseMemoryRequirements _impl_vkGetImageSparseMemoryRequirements;
void vkGetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* 
        pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements 
        ){
  if(!_impl_vkGetImageSparseMemoryRequirements) _needLoad(); 
  _impl_vkGetImageSparseMemoryRequirements(device,image,pSparseMemoryRequirementCount,pSparseMemoryRequirements);
}
static PFN_vkCmdWriteTimestamp _impl_vkCmdWriteTimestamp;
void vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, 
        VkQueryPool queryPool, uint32_t query ){
  if(!_impl_vkCmdWriteTimestamp) _needLoad(); 
  _impl_vkCmdWriteTimestamp(commandBuffer,pipelineStage,queryPool,query);
}
static PFN_vkDestroyPipelineCache _impl_vkDestroyPipelineCache;
void vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const 
        VkAllocationCallbacks* pAllocator ){
  if(!_impl_vkDestroyPipelineCache) _needLoad(); 
  _impl_vkDestroyPipelineCache(device,pipelineCache,pAllocator);
}
static PFN_vkMergePipelineCaches _impl_vkMergePipelineCaches;
VkResult vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t 
        srcCacheCount, const VkPipelineCache* pSrcCaches ){
  if(!_impl_vkMergePipelineCaches) _needLoad(); 
  return _impl_vkMergePipelineCaches(device,dstCache,srcCacheCount,pSrcCaches);
}
static PFN_vkCmdPushConstants _impl_vkCmdPushConstants;
void vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags 
        stageFlags, uint32_t offset, uint32_t size, const void* pValues ){
  if(!_impl_vkCmdPushConstants) _needLoad(); 
  _impl_vkCmdPushConstants(commandBuffer,layout,stageFlags,offset,size,pValues);
}
static PFN_vkCmdBindPipeline _impl_vkCmdBindPipeline;
void vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, 
        VkPipeline pipeline ){
  if(!_impl_vkCmdBindPipeline) _needLoad(); 
  _impl_vkCmdBindPipeline(commandBuffer,pipelineBindPoint,pipeline);
}
static PFN_vkCmdSetStencilWriteMask _impl_vkCmdSetStencilWriteMask;
void vkCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, 
        uint32_t writeMask ){
  if(!_impl_vkCmdSetStencilWriteMask) _needLoad(); 
  _impl_vkCmdSetStencilWriteMask(commandBuffer,faceMask,writeMask);
}
static PFN_vkEnumerateDeviceExtensionProperties _impl_vkEnumerateDeviceExtensionProperties;
VkResult vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const 
        char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties 
        ){
  if(!_impl_vkEnumerateDeviceExtensionProperties) _needLoad(); 
  return _impl_vkEnumerateDeviceExtensionProperties(physicalDevice,pLayerName,pPropertyCount,pProperties);
}
static PFN_vkCmdClearAttachments _impl_vkCmdClearAttachments;
void vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, 
        const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* 
        pRects ){
  if(!_impl_vkCmdClearAttachments) _needLoad(); 
  _impl_vkCmdClearAttachments(commandBuffer,attachmentCount,pAttachments,rectCount,pRects);
}
static PFN_vkBindBufferMemory _impl_vkBindBufferMemory;
VkResult vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, 
        VkDeviceSize memoryOffset ){
  if(!_impl_vkBindBufferMemory) _needLoad(); 
  return _impl_vkBindBufferMemory(device,buffer,memory,memoryOffset);
}
static PFN_vkFreeDescriptorSets _impl_vkFreeDescriptorSets;
VkResult vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t 
        descriptorSetCount, const VkDescriptorSet* pDescriptorSets ){
  if(!_impl_vkFreeDescriptorSets) _needLoad(); 
  return _impl_vkFreeDescriptorSets(device,descriptorPool,descriptorSetCount,pDescriptorSets);
}
static PFN_vkCmdResolveImage _impl_vkCmdResolveImage;
void vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const VkImageResolve* pRegions ){
  if(!_impl_vkCmdResolveImage) _needLoad(); 
  _impl_vkCmdResolveImage(commandBuffer,srcImage,srcImageLayout,dstImage,dstImageLayout,regionCount,pRegions);
}
static PFN_vkCmdEndQuery _impl_vkCmdEndQuery;
void vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t 
        query ){
  if(!_impl_vkCmdEndQuery) _needLoad(); 
  _impl_vkCmdEndQuery(commandBuffer,queryPool,query);
}
static PFN_vkGetQueryPoolResults _impl_vkGetQueryPoolResults;
VkResult vkGetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, 
        uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags 
        flags ){
  if(!_impl_vkGetQueryPoolResults) _needLoad(); 
  return _impl_vkGetQueryPoolResults(device,queryPool,firstQuery,queryCount,dataSize,pData,stride,flags);
}
static PFN_vkCmdExecuteCommands _impl_vkCmdExecuteCommands;
void vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, 
        const VkCommandBuffer* pCommandBuffers ){
  if(!_impl_vkCmdExecuteCommands) _needLoad(); 
  _impl_vkCmdExecuteCommands(commandBuffer,commandBufferCount,pCommandBuffers);
}
static PFN_vkQueuePresentKHR _impl_vkQueuePresentKHR;
VkResult vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo ){
  if(!_impl_vkQueuePresentKHR) _needLoad(); 
  return _impl_vkQueuePresentKHR(queue,pPresentInfo);
}
static PFN_vkDestroyBufferView _impl_vkDestroyBufferView;
void vkDestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroyBufferView) _needLoad(); 
  _impl_vkDestroyBufferView(device,bufferView,pAllocator);
}
static PFN_vkEnumerateInstanceLayerProperties _impl_vkEnumerateInstanceLayerProperties;
VkResult vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* 
        pProperties ){
  if(!_impl_vkEnumerateInstanceLayerProperties) _needLoad(); 
  return _impl_vkEnumerateInstanceLayerProperties(pPropertyCount,pProperties);
}
static PFN_vkCmdCopyBufferToImage _impl_vkCmdCopyBufferToImage;
void vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage 
        dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* 
        pRegions ){
  if(!_impl_vkCmdCopyBufferToImage) _needLoad(); 
  _impl_vkCmdCopyBufferToImage(commandBuffer,srcBuffer,dstImage,dstImageLayout,regionCount,pRegions);
}
static PFN_vkDestroyInstance _impl_vkDestroyInstance;
void vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator 
        ){
  if(!_impl_vkDestroyInstance) _needLoad(); 
  _impl_vkDestroyInstance(instance,pAllocator);
}
static PFN_vkGetInstanceProcAddr _impl_vkGetInstanceProcAddr;
PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance instance, const char* pName ){
  if(!_impl_vkGetInstanceProcAddr) _needLoad(); 
  return _impl_vkGetInstanceProcAddr(instance,pName);
}
static PFN_vkCreateDescriptorSetLayout _impl_vkCreateDescriptorSetLayout;
VkResult vkCreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* 
        pSetLayout ){
  if(!_impl_vkCreateDescriptorSetLayout) _needLoad(); 
  return _impl_vkCreateDescriptorSetLayout(device,pCreateInfo,pAllocator,pSetLayout);
}
static PFN_vkCreateComputePipelines _impl_vkCreateComputePipelines;
VkResult vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, 
        const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines ){
  if(!_impl_vkCreateComputePipelines) _needLoad(); 
  return _impl_vkCreateComputePipelines(device,pipelineCache,createInfoCount,pCreateInfos,pAllocator,pPipelines);
}
static PFN_vkDestroySampler _impl_vkDestroySampler;
void vkDestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroySampler) _needLoad(); 
  _impl_vkDestroySampler(device,sampler,pAllocator);
}
static PFN_vkCmdSetEvent _impl_vkCmdSetEvent;
void vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags 
        stageMask ){
  if(!_impl_vkCmdSetEvent) _needLoad(); 
  _impl_vkCmdSetEvent(commandBuffer,event,stageMask);
}
static PFN_vkCmdNextSubpass _impl_vkCmdNextSubpass;
void vkCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents ){
  if(!_impl_vkCmdNextSubpass) _needLoad(); 
  _impl_vkCmdNextSubpass(commandBuffer,contents);
}
static PFN_vkCmdSetScissor _impl_vkCmdSetScissor;
void vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t 
        scissorCount, const VkRect2D* pScissors ){
  if(!_impl_vkCmdSetScissor) _needLoad(); 
  _impl_vkCmdSetScissor(commandBuffer,firstScissor,scissorCount,pScissors);
}
static PFN_vkCmdDrawIndirect _impl_vkCmdDrawIndirect;
void vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize 
        offset, uint32_t drawCount, uint32_t stride ){
  if(!_impl_vkCmdDrawIndirect) _needLoad(); 
  _impl_vkCmdDrawIndirect(commandBuffer,buffer,offset,drawCount,stride);
}
static PFN_vkCreateBufferView _impl_vkCreateBufferView;
VkResult vkCreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkBufferView* pView ){
  if(!_impl_vkCreateBufferView) _needLoad(); 
  return _impl_vkCreateBufferView(device,pCreateInfo,pAllocator,pView);
}
static PFN_vkCmdDrawIndexed _impl_vkCmdDrawIndexed;
void vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t 
        instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance 
        ){
  if(!_impl_vkCmdDrawIndexed) _needLoad(); 
  _impl_vkCmdDrawIndexed(commandBuffer,indexCount,instanceCount,firstIndex,vertexOffset,firstInstance);
}
static PFN_vkCmdBindDescriptorSets _impl_vkCmdBindDescriptorSets;
void vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, 
        VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, 
        const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const 
        uint32_t* pDynamicOffsets ){
  if(!_impl_vkCmdBindDescriptorSets) _needLoad(); 
  _impl_vkCmdBindDescriptorSets(commandBuffer,pipelineBindPoint,layout,firstSet,descriptorSetCount,pDescriptorSets,dynamicOffsetCount,pDynamicOffsets);
}
static PFN_vkDestroySwapchainKHR _impl_vkDestroySwapchainKHR;
void vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroySwapchainKHR) _needLoad(); 
  _impl_vkDestroySwapchainKHR(device,swapchain,pAllocator);
}
static PFN_vkDestroyBuffer _impl_vkDestroyBuffer;
void vkDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroyBuffer) _needLoad(); 
  _impl_vkDestroyBuffer(device,buffer,pAllocator);
}
static PFN_vkCmdBlitImage _impl_vkCmdBlitImage;
void vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const VkImageBlit* pRegions, VkFilter filter ){
  if(!_impl_vkCmdBlitImage) _needLoad(); 
  _impl_vkCmdBlitImage(commandBuffer,srcImage,srcImageLayout,dstImage,dstImageLayout,regionCount,pRegions,filter);
}
static PFN_vkGetPhysicalDeviceSurfaceFormatsKHR _impl_vkGetPhysicalDeviceSurfaceFormatsKHR;
VkResult vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR 
        surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats 
        ){
  if(!_impl_vkGetPhysicalDeviceSurfaceFormatsKHR) _needLoad(); 
  return _impl_vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,surface,pSurfaceFormatCount,pSurfaceFormats);
}
static PFN_vkCmdEndRenderPass _impl_vkCmdEndRenderPass;
void vkCmdEndRenderPass(VkCommandBuffer commandBuffer ){
  if(!_impl_vkCmdEndRenderPass) _needLoad(); 
  _impl_vkCmdEndRenderPass(commandBuffer);
}
static PFN_vkCreateDescriptorPool _impl_vkCreateDescriptorPool;
VkResult vkCreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool 
        ){
  if(!_impl_vkCreateDescriptorPool) _needLoad(); 
  return _impl_vkCreateDescriptorPool(device,pCreateInfo,pAllocator,pDescriptorPool);
}
static PFN_vkQueueBindSparse _impl_vkQueueBindSparse;
VkResult vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* 
        pBindInfo, VkFence fence ){
  if(!_impl_vkQueueBindSparse) _needLoad(); 
  return _impl_vkQueueBindSparse(queue,bindInfoCount,pBindInfo,fence);
}
static PFN_vkCmdResetQueryPool _impl_vkCmdResetQueryPool;
void vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t 
        firstQuery, uint32_t queryCount ){
  if(!_impl_vkCmdResetQueryPool) _needLoad(); 
  _impl_vkCmdResetQueryPool(commandBuffer,queryPool,firstQuery,queryCount);
}
static PFN_vkGetPhysicalDeviceImageFormatProperties _impl_vkGetPhysicalDeviceImageFormatProperties;
VkResult vkGetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, 
        VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags 
        usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties 
        ){
  if(!_impl_vkGetPhysicalDeviceImageFormatProperties) _needLoad(); 
  return _impl_vkGetPhysicalDeviceImageFormatProperties(physicalDevice,format,type,tiling,usage,flags,pImageFormatProperties);
}
static PFN_vkFlushMappedMemoryRanges _impl_vkFlushMappedMemoryRanges;
VkResult vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const 
        VkMappedMemoryRange* pMemoryRanges ){
  if(!_impl_vkFlushMappedMemoryRanges) _needLoad(); 
  return _impl_vkFlushMappedMemoryRanges(device,memoryRangeCount,pMemoryRanges);
}
static PFN_vkCreateSemaphore _impl_vkCreateSemaphore;
VkResult vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore ){
  if(!_impl_vkCreateSemaphore) _needLoad(); 
  return _impl_vkCreateSemaphore(device,pCreateInfo,pAllocator,pSemaphore);
}
static PFN_vkDestroyShaderModule _impl_vkDestroyShaderModule;
void vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroyShaderModule) _needLoad(); 
  _impl_vkDestroyShaderModule(device,shaderModule,pAllocator);
}
static PFN_vkCmdSetBlendConstants _impl_vkCmdSetBlendConstants;
void vkCmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4] 
        ){
  if(!_impl_vkCmdSetBlendConstants) _needLoad(); 
  _impl_vkCmdSetBlendConstants(commandBuffer,blendConstants);
}
static PFN_vkCreatePipelineCache _impl_vkCreatePipelineCache;
VkResult vkCreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache 
        ){
  if(!_impl_vkCreatePipelineCache) _needLoad(); 
  return _impl_vkCreatePipelineCache(device,pCreateInfo,pAllocator,pPipelineCache);
}
static PFN_vkCreateSampler _impl_vkCreateSampler;
VkResult vkCreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkSampler* pSampler ){
  if(!_impl_vkCreateSampler) _needLoad(); 
  return _impl_vkCreateSampler(device,pCreateInfo,pAllocator,pSampler);
}
static PFN_vkCmdSetDepthBounds _impl_vkCmdSetDepthBounds;
void vkCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float 
        maxDepthBounds ){
  if(!_impl_vkCmdSetDepthBounds) _needLoad(); 
  _impl_vkCmdSetDepthBounds(commandBuffer,minDepthBounds,maxDepthBounds);
}
static PFN_vkCmdCopyImageToBuffer _impl_vkCmdCopyImageToBuffer;
void vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* 
        pRegions ){
  if(!_impl_vkCmdCopyImageToBuffer) _needLoad(); 
  _impl_vkCmdCopyImageToBuffer(commandBuffer,srcImage,srcImageLayout,dstBuffer,regionCount,pRegions);
}
static PFN_vkGetDeviceProcAddr _impl_vkGetDeviceProcAddr;
PFN_vkVoidFunction vkGetDeviceProcAddr(VkDevice device, const char* pName ){
  if(!_impl_vkGetDeviceProcAddr) _needLoad(); 
  return _impl_vkGetDeviceProcAddr(device,pName);
}
static PFN_vkGetDeviceQueue _impl_vkGetDeviceQueue;
void vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, 
        VkQueue* pQueue ){
  if(!_impl_vkGetDeviceQueue) _needLoad(); 
  _impl_vkGetDeviceQueue(device,queueFamilyIndex,queueIndex,pQueue);
}
static PFN_vkDestroyEvent _impl_vkDestroyEvent;
void vkDestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroyEvent) _needLoad(); 
  _impl_vkDestroyEvent(device,event,pAllocator);
}
static PFN_vkResetEvent _impl_vkResetEvent;
VkResult vkResetEvent(VkDevice device, VkEvent event ){
  if(!_impl_vkResetEvent) _needLoad(); 
  return _impl_vkResetEvent(device,event);
}
static PFN_vkGetBufferMemoryRequirements _impl_vkGetBufferMemoryRequirements;
void vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* 
        pMemoryRequirements ){
  if(!_impl_vkGetBufferMemoryRequirements) _needLoad(); 
  _impl_vkGetBufferMemoryRequirements(device,buffer,pMemoryRequirements);
}
static PFN_vkAllocateCommandBuffers _impl_vkAllocateCommandBuffers;
VkResult vkAllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* 
        pAllocateInfo, VkCommandBuffer* pCommandBuffers ){
  if(!_impl_vkAllocateCommandBuffers) _needLoad(); 
  return _impl_vkAllocateCommandBuffers(device,pAllocateInfo,pCommandBuffers);
}
static PFN_vkCreateImageView _impl_vkCreateImageView;
VkResult vkCreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkImageView* pView ){
  if(!_impl_vkCreateImageView) _needLoad(); 
  return _impl_vkCreateImageView(device,pCreateInfo,pAllocator,pView);
}
static PFN_vkCmdBindVertexBuffers _impl_vkCmdBindVertexBuffers;
void vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, 
        uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets 
        ){
  if(!_impl_vkCmdBindVertexBuffers) _needLoad(); 
  _impl_vkCmdBindVertexBuffers(commandBuffer,firstBinding,bindingCount,pBuffers,pOffsets);
}
static PFN_vkAcquireNextImageKHR _impl_vkAcquireNextImageKHR;
VkResult vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t 
        timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex ){
  if(!_impl_vkAcquireNextImageKHR) _needLoad(); 
  return _impl_vkAcquireNextImageKHR(device,swapchain,timeout,semaphore,fence,pImageIndex);
}
static PFN_vkQueueEndDebugUtilsLabelEXT _impl_vkQueueEndDebugUtilsLabelEXT;
void vkQueueEndDebugUtilsLabelEXT(VkQueue queue ){
  if(!_impl_vkQueueEndDebugUtilsLabelEXT) _needLoad(); 
  _impl_vkQueueEndDebugUtilsLabelEXT(queue);
}
static PFN_vkCreateFence _impl_vkCreateFence;
VkResult vkCreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkFence* pFence ){
  if(!_impl_vkCreateFence) _needLoad(); 
  return _impl_vkCreateFence(device,pCreateInfo,pAllocator,pFence);
}
static PFN_vkCreateRenderPass _impl_vkCreateRenderPass;
VkResult vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass ){
  if(!_impl_vkCreateRenderPass) _needLoad(); 
  return _impl_vkCreateRenderPass(device,pCreateInfo,pAllocator,pRenderPass);
}
static PFN_vkDestroySemaphore _impl_vkDestroySemaphore;
void vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroySemaphore) _needLoad(); 
  _impl_vkDestroySemaphore(device,semaphore,pAllocator);
}
static PFN_vkQueueBeginDebugUtilsLabelEXT _impl_vkQueueBeginDebugUtilsLabelEXT;
void vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo 
        ){
  if(!_impl_vkQueueBeginDebugUtilsLabelEXT) _needLoad(); 
  _impl_vkQueueBeginDebugUtilsLabelEXT(queue,pLabelInfo);
}
static PFN_vkBindImageMemory _impl_vkBindImageMemory;
VkResult vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, 
        VkDeviceSize memoryOffset ){
  if(!_impl_vkBindImageMemory) _needLoad(); 
  return _impl_vkBindImageMemory(device,image,memory,memoryOffset);
}
static PFN_vkGetPhysicalDeviceSurfacePresentModesKHR _impl_vkGetPhysicalDeviceSurfacePresentModesKHR;
VkResult vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, 
        VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes 
        ){
  if(!_impl_vkGetPhysicalDeviceSurfacePresentModesKHR) _needLoad(); 
  return _impl_vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice,surface,pPresentModeCount,pPresentModes);
}
static PFN_vkCreateInstance _impl_vkCreateInstance;
VkResult vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* 
        pAllocator, VkInstance* pInstance ){
  if(!_impl_vkCreateInstance) _needLoad(); 
  return _impl_vkCreateInstance(pCreateInfo,pAllocator,pInstance);
}
static PFN_vkDestroyFence _impl_vkDestroyFence;
void vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroyFence) _needLoad(); 
  _impl_vkDestroyFence(device,fence,pAllocator);
}
static PFN_vkDeviceWaitIdle _impl_vkDeviceWaitIdle;
VkResult vkDeviceWaitIdle(VkDevice device ){
  if(!_impl_vkDeviceWaitIdle) _needLoad(); 
  return _impl_vkDeviceWaitIdle(device);
}
static PFN_vkResetFences _impl_vkResetFences;
VkResult vkResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences 
        ){
  if(!_impl_vkResetFences) _needLoad(); 
  return _impl_vkResetFences(device,fenceCount,pFences);
}
static PFN_vkDestroySurfaceKHR _impl_vkDestroySurfaceKHR;
void vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroySurfaceKHR) _needLoad(); 
  _impl_vkDestroySurfaceKHR(instance,surface,pAllocator);
}
static PFN_vkCmdInsertDebugUtilsLabelEXT _impl_vkCmdInsertDebugUtilsLabelEXT;
void vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* 
        pLabelInfo ){
  if(!_impl_vkCmdInsertDebugUtilsLabelEXT) _needLoad(); 
  _impl_vkCmdInsertDebugUtilsLabelEXT(commandBuffer,pLabelInfo);
}
static PFN_vkCreatePipelineLayout _impl_vkCreatePipelineLayout;
VkResult vkCreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout 
        ){
  if(!_impl_vkCreatePipelineLayout) _needLoad(); 
  return _impl_vkCreatePipelineLayout(device,pCreateInfo,pAllocator,pPipelineLayout);
}
static PFN_vkSetEvent _impl_vkSetEvent;
VkResult vkSetEvent(VkDevice device, VkEvent event ){
  if(!_impl_vkSetEvent) _needLoad(); 
  return _impl_vkSetEvent(device,event);
}
static PFN_vkDestroyCommandPool _impl_vkDestroyCommandPool;
void vkDestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* 
        pAllocator ){
  if(!_impl_vkDestroyCommandPool) _needLoad(); 
  _impl_vkDestroyCommandPool(device,commandPool,pAllocator);
}
static PFN_vkUpdateDescriptorSets _impl_vkUpdateDescriptorSets;
void vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const 
        VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const 
        VkCopyDescriptorSet* pDescriptorCopies ){
  if(!_impl_vkUpdateDescriptorSets) _needLoad(); 
  _impl_vkUpdateDescriptorSets(device,descriptorWriteCount,pDescriptorWrites,descriptorCopyCount,pDescriptorCopies);
}
static PFN_vkResetCommandPool _impl_vkResetCommandPool;
VkResult vkResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags 
        flags ){
  if(!_impl_vkResetCommandPool) _needLoad(); 
  return _impl_vkResetCommandPool(device,commandPool,flags);
}
static PFN_vkCmdDispatchIndirect _impl_vkCmdDispatchIndirect;
void vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize 
        offset ){
  if(!_impl_vkCmdDispatchIndirect) _needLoad(); 
  _impl_vkCmdDispatchIndirect(commandBuffer,buffer,offset);
}
static PFN_vkInvalidateMappedMemoryRanges _impl_vkInvalidateMappedMemoryRanges;
VkResult vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, 
        const VkMappedMemoryRange* pMemoryRanges ){
  if(!_impl_vkInvalidateMappedMemoryRanges) _needLoad(); 
  return _impl_vkInvalidateMappedMemoryRanges(device,memoryRangeCount,pMemoryRanges);
}
static PFN_vkResetDescriptorPool _impl_vkResetDescriptorPool;
VkResult vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, 
        VkDescriptorPoolResetFlags flags ){
  if(!_impl_vkResetDescriptorPool) _needLoad(); 
  return _impl_vkResetDescriptorPool(device,descriptorPool,flags);
}
static PFN_vkAllocateDescriptorSets _impl_vkAllocateDescriptorSets;
VkResult vkAllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* 
        pAllocateInfo, VkDescriptorSet* pDescriptorSets ){
  if(!_impl_vkAllocateDescriptorSets) _needLoad(); 
  return _impl_vkAllocateDescriptorSets(device,pAllocateInfo,pDescriptorSets);
}
static PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR _impl_vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
VkResult vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, 
        VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities ){
  if(!_impl_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) _needLoad(); 
  return _impl_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice,surface,pSurfaceCapabilities);
}
static PFN_vkGetPhysicalDeviceQueueFamilyProperties _impl_vkGetPhysicalDeviceQueueFamilyProperties;
void vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* 
        pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties 
        ){
  if(!_impl_vkGetPhysicalDeviceQueueFamilyProperties) _needLoad(); 
  _impl_vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice,pQueueFamilyPropertyCount,pQueueFamilyProperties);
}
 
void loadSpecialVulkanFunctions()
{
    _impl_vkCreateInstance = (PFN_vkCreateInstance) loadVulkanFunction(nullptr, "vkCreateInstance");
    /*VK1.1 
    vkEnumerateInstanceVersion = 
        (PFN_vkEnumerateInstanceVersion) loadVulkanFunction(
            nullptr, 
            "vkEnumerateInstanceVersion");
    */
    _impl_vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties) loadVulkanFunction(nullptr, "vkEnumerateInstanceExtensionProperties");
    _impl_vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties) loadVulkanFunction(nullptr, "vkEnumerateInstanceLayerProperties");
}
void vkGetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource& 
        pSubresource, VkSubresourceLayout* pLayout ){
    auto pSubresource_copy = pSubresource;
    vkGetImageSubresourceLayout(device,image,&pSubresource_copy,pLayout);
}
VkResult vkSetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT& 
        pTagInfo ){
    auto pTagInfo_copy = pTagInfo;
    pTagInfo_copy.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
    return vkSetDebugUtilsObjectTagEXT(device,&pTagInfo_copy);
}
void vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT 
        messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT& 
        pCallbackData ){
    auto pCallbackData_copy = pCallbackData;
    pCallbackData_copy.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT;
    vkSubmitDebugUtilsMessageEXT(instance,messageSeverity,messageTypes,&pCallbackData_copy);
}
VkResult vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    return vkCreateCommandPool(device,&pCreateInfo_copy,pAllocator,pCommandPool);
}
void vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* 
        pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, 
        uint32_t memoryBarrierCount, const VkMemoryBarrier& pMemoryBarriers, uint32_t 
        bufferMemoryBarrierCount, const VkBufferMemoryBarrier& pBufferMemoryBarriers, 
        uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier& pImageMemoryBarriers 
        ){
    auto pMemoryBarriers_copy = pMemoryBarriers;
    pMemoryBarriers_copy.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
    auto pBufferMemoryBarriers_copy = pBufferMemoryBarriers;
    pBufferMemoryBarriers_copy.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    auto pImageMemoryBarriers_copy = pImageMemoryBarriers;
    pImageMemoryBarriers_copy.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    vkCmdWaitEvents(commandBuffer,eventCount,pEvents,srcStageMask,dstStageMask,memoryBarrierCount,&pMemoryBarriers_copy,bufferMemoryBarrierCount,&pBufferMemoryBarriers_copy,imageMemoryBarrierCount,&pImageMemoryBarriers_copy);
}
VkResult vkCreateImage(VkDevice device, const VkImageCreateInfo& pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkImage* pImage ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    return vkCreateImage(device,&pCreateInfo_copy,pAllocator,pImage);
}
void vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT& 
        pLabelInfo ){
    auto pLabelInfo_copy = pLabelInfo;
    pLabelInfo_copy.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    vkCmdBeginDebugUtilsLabelEXT(commandBuffer,&pLabelInfo_copy);
}
VkResult vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    return vkCreateDevice(physicalDevice,&pCreateInfo_copy,pAllocator,pDevice);
}
VkResult vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo& pAllocateInfo, 
        const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory ){
    auto pAllocateInfo_copy = pAllocateInfo;
    pAllocateInfo_copy.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    return vkAllocateMemory(device,&pAllocateInfo_copy,pAllocator,pMemory);
}
VkResult vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    return vkCreateSwapchainKHR(device,&pCreateInfo_copy,pAllocator,pSwapchain);
}
void vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo& 
        pRenderPassBegin, VkSubpassContents contents ){
    auto pRenderPassBegin_copy = pRenderPassBegin;
    pRenderPassBegin_copy.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    vkCmdBeginRenderPass(commandBuffer,&pRenderPassBegin_copy,contents);
}
VkResult vkCreateBuffer(VkDevice device, const VkBufferCreateInfo& pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    return vkCreateBuffer(device,&pCreateInfo_copy,pAllocator,pBuffer);
}
VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* 
        pMessenger ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    return vkCreateDebugUtilsMessengerEXT(instance,&pCreateInfo_copy,pAllocator,pMessenger);
}
void vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer 
        dstBuffer, uint32_t regionCount, const VkBufferCopy& pRegions ){
    auto pRegions_copy = pRegions;
    vkCmdCopyBuffer(commandBuffer,srcBuffer,dstBuffer,regionCount,&pRegions_copy);
}
VkResult vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo& pSubmits, 
        VkFence fence ){
    auto pSubmits_copy = pSubmits;
    pSubmits_copy.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    return vkQueueSubmit(queue,submitCount,&pSubmits_copy,fence);
}
VkResult vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo& pCreateInfos, 
        const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines ){
    auto pCreateInfos_copy = pCreateInfos;
    pCreateInfos_copy.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    return vkCreateGraphicsPipelines(device,pipelineCache,createInfoCount,&pCreateInfos_copy,pAllocator,pPipelines);
}
void vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const VkClearDepthStencilValue& pDepthStencil, uint32_t rangeCount, 
        const VkImageSubresourceRange& pRanges ){
    auto pDepthStencil_copy = pDepthStencil;
    auto pRanges_copy = pRanges;
    vkCmdClearDepthStencilImage(commandBuffer,image,imageLayout,&pDepthStencil_copy,rangeCount,&pRanges_copy);
}
VkResult vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo& 
        pBeginInfo ){
    auto pBeginInfo_copy = pBeginInfo;
    pBeginInfo_copy.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    return vkBeginCommandBuffer(commandBuffer,&pBeginInfo_copy);
}
void vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, 
        VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t 
        memoryBarrierCount, const VkMemoryBarrier& pMemoryBarriers, uint32_t bufferMemoryBarrierCount, 
        const VkBufferMemoryBarrier& pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, 
        const VkImageMemoryBarrier& pImageMemoryBarriers ){
    auto pMemoryBarriers_copy = pMemoryBarriers;
    pMemoryBarriers_copy.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
    auto pBufferMemoryBarriers_copy = pBufferMemoryBarriers;
    pBufferMemoryBarriers_copy.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    auto pImageMemoryBarriers_copy = pImageMemoryBarriers;
    pImageMemoryBarriers_copy.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    vkCmdPipelineBarrier(commandBuffer,srcStageMask,dstStageMask,dependencyFlags,memoryBarrierCount,&pMemoryBarriers_copy,bufferMemoryBarrierCount,&pBufferMemoryBarriers_copy,imageMemoryBarrierCount,&pImageMemoryBarriers_copy);
}
VkResult vkCreateEvent(VkDevice device, const VkEventCreateInfo& pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkEvent* pEvent ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
    return vkCreateEvent(device,&pCreateInfo_copy,pAllocator,pEvent);
}
void vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const VkImageCopy& pRegions ){
    auto pRegions_copy = pRegions;
    vkCmdCopyImage(commandBuffer,srcImage,srcImageLayout,dstImage,dstImageLayout,regionCount,&pRegions_copy);
}
void vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const VkClearColorValue& pColor, uint32_t rangeCount, const 
        VkImageSubresourceRange& pRanges ){
    auto pColor_copy = pColor;
    auto pRanges_copy = pRanges;
    vkCmdClearColorImage(commandBuffer,image,imageLayout,&pColor_copy,rangeCount,&pRanges_copy);
}
VkResult vkSetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT& 
        pNameInfo ){
    auto pNameInfo_copy = pNameInfo;
    pNameInfo_copy.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
    return vkSetDebugUtilsObjectNameEXT(device,&pNameInfo_copy);
}
void vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t 
        viewportCount, const VkViewport& pViewports ){
    auto pViewports_copy = pViewports;
    vkCmdSetViewport(commandBuffer,firstViewport,viewportCount,&pViewports_copy);
}
VkResult vkCreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    return vkCreateQueryPool(device,&pCreateInfo_copy,pAllocator,pQueryPool);
}
VkResult vkCreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    return vkCreateShaderModule(device,&pCreateInfo_copy,pAllocator,pShaderModule);
}
VkResult vkCreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    return vkCreateFramebuffer(device,&pCreateInfo_copy,pAllocator,pFramebuffer);
}
void vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT& pLabelInfo 
        ){
    auto pLabelInfo_copy = pLabelInfo;
    pLabelInfo_copy.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    vkQueueInsertDebugUtilsLabelEXT(queue,&pLabelInfo_copy);
}
void vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, 
        const VkClearAttachment& pAttachments, uint32_t rectCount, const VkClearRect& 
        pRects ){
    auto pAttachments_copy = pAttachments;
    auto pRects_copy = pRects;
    vkCmdClearAttachments(commandBuffer,attachmentCount,&pAttachments_copy,rectCount,&pRects_copy);
}
void vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const VkImageResolve& pRegions ){
    auto pRegions_copy = pRegions;
    vkCmdResolveImage(commandBuffer,srcImage,srcImageLayout,dstImage,dstImageLayout,regionCount,&pRegions_copy);
}
VkResult vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR& pPresentInfo ){
    auto pPresentInfo_copy = pPresentInfo;
    pPresentInfo_copy.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    return vkQueuePresentKHR(queue,&pPresentInfo_copy);
}
void vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage 
        dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy& 
        pRegions ){
    auto pRegions_copy = pRegions;
    vkCmdCopyBufferToImage(commandBuffer,srcBuffer,dstImage,dstImageLayout,regionCount,&pRegions_copy);
}
VkResult vkCreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* 
        pSetLayout ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    return vkCreateDescriptorSetLayout(device,&pCreateInfo_copy,pAllocator,pSetLayout);
}
VkResult vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const VkComputePipelineCreateInfo& pCreateInfos, 
        const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines ){
    auto pCreateInfos_copy = pCreateInfos;
    pCreateInfos_copy.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    return vkCreateComputePipelines(device,pipelineCache,createInfoCount,&pCreateInfos_copy,pAllocator,pPipelines);
}
void vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t 
        scissorCount, const VkRect2D& pScissors ){
    auto pScissors_copy = pScissors;
    vkCmdSetScissor(commandBuffer,firstScissor,scissorCount,&pScissors_copy);
}
VkResult vkCreateBufferView(VkDevice device, const VkBufferViewCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkBufferView* pView ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    return vkCreateBufferView(device,&pCreateInfo_copy,pAllocator,pView);
}
void vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const VkImageBlit& pRegions, VkFilter filter ){
    auto pRegions_copy = pRegions;
    vkCmdBlitImage(commandBuffer,srcImage,srcImageLayout,dstImage,dstImageLayout,regionCount,&pRegions_copy,filter);
}
VkResult vkCreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    return vkCreateDescriptorPool(device,&pCreateInfo_copy,pAllocator,pDescriptorPool);
}
VkResult vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo& 
        pBindInfo, VkFence fence ){
    auto pBindInfo_copy = pBindInfo;
    pBindInfo_copy.sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO;
    return vkQueueBindSparse(queue,bindInfoCount,&pBindInfo_copy,fence);
}
VkResult vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const 
        VkMappedMemoryRange& pMemoryRanges ){
    auto pMemoryRanges_copy = pMemoryRanges;
    pMemoryRanges_copy.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    return vkFlushMappedMemoryRanges(device,memoryRangeCount,&pMemoryRanges_copy);
}
VkResult vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    return vkCreateSemaphore(device,&pCreateInfo_copy,pAllocator,pSemaphore);
}
VkResult vkCreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    return vkCreatePipelineCache(device,&pCreateInfo_copy,pAllocator,pPipelineCache);
}
VkResult vkCreateSampler(VkDevice device, const VkSamplerCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkSampler* pSampler ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    return vkCreateSampler(device,&pCreateInfo_copy,pAllocator,pSampler);
}
void vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy& 
        pRegions ){
    auto pRegions_copy = pRegions;
    vkCmdCopyImageToBuffer(commandBuffer,srcImage,srcImageLayout,dstBuffer,regionCount,&pRegions_copy);
}
VkResult vkAllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo& 
        pAllocateInfo, VkCommandBuffer* pCommandBuffers ){
    auto pAllocateInfo_copy = pAllocateInfo;
    pAllocateInfo_copy.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    return vkAllocateCommandBuffers(device,&pAllocateInfo_copy,pCommandBuffers);
}
VkResult vkCreateImageView(VkDevice device, const VkImageViewCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkImageView* pView ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    return vkCreateImageView(device,&pCreateInfo_copy,pAllocator,pView);
}
VkResult vkCreateFence(VkDevice device, const VkFenceCreateInfo& pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkFence* pFence ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    return vkCreateFence(device,&pCreateInfo_copy,pAllocator,pFence);
}
VkResult vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    return vkCreateRenderPass(device,&pCreateInfo_copy,pAllocator,pRenderPass);
}
void vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT& pLabelInfo 
        ){
    auto pLabelInfo_copy = pLabelInfo;
    pLabelInfo_copy.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    vkQueueBeginDebugUtilsLabelEXT(queue,&pLabelInfo_copy);
}
VkResult vkCreateInstance(const VkInstanceCreateInfo& pCreateInfo, const VkAllocationCallbacks* 
        pAllocator, VkInstance* pInstance ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    return vkCreateInstance(&pCreateInfo_copy,pAllocator,pInstance);
}
void vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT& 
        pLabelInfo ){
    auto pLabelInfo_copy = pLabelInfo;
    pLabelInfo_copy.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    vkCmdInsertDebugUtilsLabelEXT(commandBuffer,&pLabelInfo_copy);
}
VkResult vkCreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    pCreateInfo_copy.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    return vkCreatePipelineLayout(device,&pCreateInfo_copy,pAllocator,pPipelineLayout);
}
void vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const 
        VkWriteDescriptorSet& pDescriptorWrites, uint32_t descriptorCopyCount, const 
        VkCopyDescriptorSet& pDescriptorCopies ){
    auto pDescriptorWrites_copy = pDescriptorWrites;
    pDescriptorWrites_copy.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    auto pDescriptorCopies_copy = pDescriptorCopies;
    pDescriptorCopies_copy.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
    vkUpdateDescriptorSets(device,descriptorWriteCount,&pDescriptorWrites_copy,descriptorCopyCount,&pDescriptorCopies_copy);
}
VkResult vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, 
        const VkMappedMemoryRange& pMemoryRanges ){
    auto pMemoryRanges_copy = pMemoryRanges;
    pMemoryRanges_copy.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    return vkInvalidateMappedMemoryRanges(device,memoryRangeCount,&pMemoryRanges_copy);
}
VkResult vkAllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo& 
        pAllocateInfo, VkDescriptorSet* pDescriptorSets ){
    auto pAllocateInfo_copy = pAllocateInfo;
    pAllocateInfo_copy.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    return vkAllocateDescriptorSets(device,&pAllocateInfo_copy,pDescriptorSets);
}
void vkGetImageSubresourceLayout(VkDevice device, VkImage image, const std::vector<VkImageSubresource>& 
        pSubresource, VkSubresourceLayout* pLayout ){
    auto pSubresource_copy = pSubresource;
    vkGetImageSubresourceLayout(device,image,pSubresource_copy.data(),pLayout);
}
VkResult vkSetDebugUtilsObjectTagEXT(VkDevice device, const std::vector<VkDebugUtilsObjectTagInfoEXT>& 
        pTagInfo ){
    auto pTagInfo_copy = pTagInfo;
    for(auto& item : pTagInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
    return vkSetDebugUtilsObjectTagEXT(device,pTagInfo_copy.data());
}
void vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT 
        messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const std::vector<VkDebugUtilsMessengerCallbackDataEXT>& 
        pCallbackData ){
    auto pCallbackData_copy = pCallbackData;
    for(auto& item : pCallbackData_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT;
    vkSubmitDebugUtilsMessageEXT(instance,messageSeverity,messageTypes,pCallbackData_copy.data());
}
VkResult vkCreateCommandPool(VkDevice device, const std::vector<VkCommandPoolCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    return vkCreateCommandPool(device,pCreateInfo_copy.data(),pAllocator,pCommandPool);
}
void vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* 
        pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, 
        uint32_t memoryBarrierCount, const std::vector<VkMemoryBarrier>& pMemoryBarriers, 
        uint32_t bufferMemoryBarrierCount, const std::vector<VkBufferMemoryBarrier>& 
        pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const std::vector<VkImageMemoryBarrier>& 
        pImageMemoryBarriers ){
    auto pMemoryBarriers_copy = pMemoryBarriers;
    for(auto& item : pMemoryBarriers_copy ) item.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
    auto pBufferMemoryBarriers_copy = pBufferMemoryBarriers;
    for(auto& item : pBufferMemoryBarriers_copy ) item.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    auto pImageMemoryBarriers_copy = pImageMemoryBarriers;
    for(auto& item : pImageMemoryBarriers_copy ) item.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    vkCmdWaitEvents(commandBuffer,eventCount,pEvents,srcStageMask,dstStageMask,memoryBarrierCount,pMemoryBarriers_copy.data(),bufferMemoryBarrierCount,pBufferMemoryBarriers_copy.data(),imageMemoryBarrierCount,pImageMemoryBarriers_copy.data());
}
VkResult vkCreateImage(VkDevice device, const std::vector<VkImageCreateInfo>& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkImage* pImage ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    return vkCreateImage(device,pCreateInfo_copy.data(),pAllocator,pImage);
}
void vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const std::vector<VkDebugUtilsLabelEXT>& 
        pLabelInfo ){
    auto pLabelInfo_copy = pLabelInfo;
    for(auto& item : pLabelInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    vkCmdBeginDebugUtilsLabelEXT(commandBuffer,pLabelInfo_copy.data());
}
VkResult vkCreateDevice(VkPhysicalDevice physicalDevice, const std::vector<VkDeviceCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    return vkCreateDevice(physicalDevice,pCreateInfo_copy.data(),pAllocator,pDevice);
}
VkResult vkAllocateMemory(VkDevice device, const std::vector<VkMemoryAllocateInfo>& 
        pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory 
        ){
    auto pAllocateInfo_copy = pAllocateInfo;
    for(auto& item : pAllocateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    return vkAllocateMemory(device,pAllocateInfo_copy.data(),pAllocator,pMemory);
}
VkResult vkCreateSwapchainKHR(VkDevice device, const std::vector<VkSwapchainCreateInfoKHR>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    return vkCreateSwapchainKHR(device,pCreateInfo_copy.data(),pAllocator,pSwapchain);
}
void vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const std::vector<VkRenderPassBeginInfo>& 
        pRenderPassBegin, VkSubpassContents contents ){
    auto pRenderPassBegin_copy = pRenderPassBegin;
    for(auto& item : pRenderPassBegin_copy ) item.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    vkCmdBeginRenderPass(commandBuffer,pRenderPassBegin_copy.data(),contents);
}
VkResult vkCreateBuffer(VkDevice device, const std::vector<VkBufferCreateInfo>& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    return vkCreateBuffer(device,pCreateInfo_copy.data(),pAllocator,pBuffer);
}
VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance, const std::vector<VkDebugUtilsMessengerCreateInfoEXT>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* 
        pMessenger ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    return vkCreateDebugUtilsMessengerEXT(instance,pCreateInfo_copy.data(),pAllocator,pMessenger);
}
void vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer 
        dstBuffer, uint32_t regionCount, const std::vector<VkBufferCopy>& pRegions 
        ){
    auto pRegions_copy = pRegions;
    vkCmdCopyBuffer(commandBuffer,srcBuffer,dstBuffer,regionCount,pRegions_copy.data());
}
VkResult vkQueueSubmit(VkQueue queue, uint32_t submitCount, const std::vector<VkSubmitInfo>& 
        pSubmits, VkFence fence ){
    auto pSubmits_copy = pSubmits;
    for(auto& item : pSubmits_copy ) item.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    return vkQueueSubmit(queue,submitCount,pSubmits_copy.data(),fence);
}
VkResult vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const std::vector<VkGraphicsPipelineCreateInfo>& 
        pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines 
        ){
    auto pCreateInfos_copy = pCreateInfos;
    for(auto& item : pCreateInfos_copy ) item.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    return vkCreateGraphicsPipelines(device,pipelineCache,createInfoCount,pCreateInfos_copy.data(),pAllocator,pPipelines);
}
void vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const std::vector<VkClearDepthStencilValue>& pDepthStencil, 
        uint32_t rangeCount, const std::vector<VkImageSubresourceRange>& pRanges 
        ){
    auto pDepthStencil_copy = pDepthStencil;
    auto pRanges_copy = pRanges;
    vkCmdClearDepthStencilImage(commandBuffer,image,imageLayout,pDepthStencil_copy.data(),rangeCount,pRanges_copy.data());
}
VkResult vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const std::vector<VkCommandBufferBeginInfo>& 
        pBeginInfo ){
    auto pBeginInfo_copy = pBeginInfo;
    for(auto& item : pBeginInfo_copy ) item.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    return vkBeginCommandBuffer(commandBuffer,pBeginInfo_copy.data());
}
void vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, 
        VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t 
        memoryBarrierCount, const std::vector<VkMemoryBarrier>& pMemoryBarriers, 
        uint32_t bufferMemoryBarrierCount, const std::vector<VkBufferMemoryBarrier>& 
        pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const std::vector<VkImageMemoryBarrier>& 
        pImageMemoryBarriers ){
    auto pMemoryBarriers_copy = pMemoryBarriers;
    for(auto& item : pMemoryBarriers_copy ) item.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
    auto pBufferMemoryBarriers_copy = pBufferMemoryBarriers;
    for(auto& item : pBufferMemoryBarriers_copy ) item.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    auto pImageMemoryBarriers_copy = pImageMemoryBarriers;
    for(auto& item : pImageMemoryBarriers_copy ) item.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    vkCmdPipelineBarrier(commandBuffer,srcStageMask,dstStageMask,dependencyFlags,memoryBarrierCount,pMemoryBarriers_copy.data(),bufferMemoryBarrierCount,pBufferMemoryBarriers_copy.data(),imageMemoryBarrierCount,pImageMemoryBarriers_copy.data());
}
VkResult vkCreateEvent(VkDevice device, const std::vector<VkEventCreateInfo>& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkEvent* pEvent ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
    return vkCreateEvent(device,pCreateInfo_copy.data(),pAllocator,pEvent);
}
void vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const std::vector<VkImageCopy>& pRegions ){
    auto pRegions_copy = pRegions;
    vkCmdCopyImage(commandBuffer,srcImage,srcImageLayout,dstImage,dstImageLayout,regionCount,pRegions_copy.data());
}
void vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const std::vector<VkClearColorValue>& pColor, uint32_t rangeCount, 
        const std::vector<VkImageSubresourceRange>& pRanges ){
    auto pColor_copy = pColor;
    auto pRanges_copy = pRanges;
    vkCmdClearColorImage(commandBuffer,image,imageLayout,pColor_copy.data(),rangeCount,pRanges_copy.data());
}
VkResult vkSetDebugUtilsObjectNameEXT(VkDevice device, const std::vector<VkDebugUtilsObjectNameInfoEXT>& 
        pNameInfo ){
    auto pNameInfo_copy = pNameInfo;
    for(auto& item : pNameInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
    return vkSetDebugUtilsObjectNameEXT(device,pNameInfo_copy.data());
}
void vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t 
        viewportCount, const std::vector<VkViewport>& pViewports ){
    auto pViewports_copy = pViewports;
    vkCmdSetViewport(commandBuffer,firstViewport,viewportCount,pViewports_copy.data());
}
VkResult vkCreateQueryPool(VkDevice device, const std::vector<VkQueryPoolCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    return vkCreateQueryPool(device,pCreateInfo_copy.data(),pAllocator,pQueryPool);
}
VkResult vkCreateShaderModule(VkDevice device, const std::vector<VkShaderModuleCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    return vkCreateShaderModule(device,pCreateInfo_copy.data(),pAllocator,pShaderModule);
}
VkResult vkCreateFramebuffer(VkDevice device, const std::vector<VkFramebufferCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    return vkCreateFramebuffer(device,pCreateInfo_copy.data(),pAllocator,pFramebuffer);
}
void vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const std::vector<VkDebugUtilsLabelEXT>& 
        pLabelInfo ){
    auto pLabelInfo_copy = pLabelInfo;
    for(auto& item : pLabelInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    vkQueueInsertDebugUtilsLabelEXT(queue,pLabelInfo_copy.data());
}
void vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, 
        const std::vector<VkClearAttachment>& pAttachments, uint32_t rectCount, const 
        std::vector<VkClearRect>& pRects ){
    auto pAttachments_copy = pAttachments;
    auto pRects_copy = pRects;
    vkCmdClearAttachments(commandBuffer,attachmentCount,pAttachments_copy.data(),rectCount,pRects_copy.data());
}
void vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const std::vector<VkImageResolve>& pRegions ){
    auto pRegions_copy = pRegions;
    vkCmdResolveImage(commandBuffer,srcImage,srcImageLayout,dstImage,dstImageLayout,regionCount,pRegions_copy.data());
}
VkResult vkQueuePresentKHR(VkQueue queue, const std::vector<VkPresentInfoKHR>& pPresentInfo 
        ){
    auto pPresentInfo_copy = pPresentInfo;
    for(auto& item : pPresentInfo_copy ) item.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    return vkQueuePresentKHR(queue,pPresentInfo_copy.data());
}
void vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage 
        dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const std::vector<VkBufferImageCopy>& 
        pRegions ){
    auto pRegions_copy = pRegions;
    vkCmdCopyBufferToImage(commandBuffer,srcBuffer,dstImage,dstImageLayout,regionCount,pRegions_copy.data());
}
VkResult vkCreateDescriptorSetLayout(VkDevice device, const std::vector<VkDescriptorSetLayoutCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* 
        pSetLayout ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    return vkCreateDescriptorSetLayout(device,pCreateInfo_copy.data(),pAllocator,pSetLayout);
}
VkResult vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const std::vector<VkComputePipelineCreateInfo>& 
        pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines 
        ){
    auto pCreateInfos_copy = pCreateInfos;
    for(auto& item : pCreateInfos_copy ) item.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    return vkCreateComputePipelines(device,pipelineCache,createInfoCount,pCreateInfos_copy.data(),pAllocator,pPipelines);
}
void vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t 
        scissorCount, const std::vector<VkRect2D>& pScissors ){
    auto pScissors_copy = pScissors;
    vkCmdSetScissor(commandBuffer,firstScissor,scissorCount,pScissors_copy.data());
}
VkResult vkCreateBufferView(VkDevice device, const std::vector<VkBufferViewCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    return vkCreateBufferView(device,pCreateInfo_copy.data(),pAllocator,pView);
}
void vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const std::vector<VkImageBlit>& pRegions, VkFilter filter ){
    auto pRegions_copy = pRegions;
    vkCmdBlitImage(commandBuffer,srcImage,srcImageLayout,dstImage,dstImageLayout,regionCount,pRegions_copy.data(),filter);
}
VkResult vkCreateDescriptorPool(VkDevice device, const std::vector<VkDescriptorPoolCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    return vkCreateDescriptorPool(device,pCreateInfo_copy.data(),pAllocator,pDescriptorPool);
}
VkResult vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const std::vector<VkBindSparseInfo>& 
        pBindInfo, VkFence fence ){
    auto pBindInfo_copy = pBindInfo;
    for(auto& item : pBindInfo_copy ) item.sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO;
    return vkQueueBindSparse(queue,bindInfoCount,pBindInfo_copy.data(),fence);
}
VkResult vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const 
        std::vector<VkMappedMemoryRange>& pMemoryRanges ){
    auto pMemoryRanges_copy = pMemoryRanges;
    for(auto& item : pMemoryRanges_copy ) item.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    return vkFlushMappedMemoryRanges(device,memoryRangeCount,pMemoryRanges_copy.data());
}
VkResult vkCreateSemaphore(VkDevice device, const std::vector<VkSemaphoreCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    return vkCreateSemaphore(device,pCreateInfo_copy.data(),pAllocator,pSemaphore);
}
VkResult vkCreatePipelineCache(VkDevice device, const std::vector<VkPipelineCacheCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    return vkCreatePipelineCache(device,pCreateInfo_copy.data(),pAllocator,pPipelineCache);
}
VkResult vkCreateSampler(VkDevice device, const std::vector<VkSamplerCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    return vkCreateSampler(device,pCreateInfo_copy.data(),pAllocator,pSampler);
}
void vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const std::vector<VkBufferImageCopy>& 
        pRegions ){
    auto pRegions_copy = pRegions;
    vkCmdCopyImageToBuffer(commandBuffer,srcImage,srcImageLayout,dstBuffer,regionCount,pRegions_copy.data());
}
VkResult vkAllocateCommandBuffers(VkDevice device, const std::vector<VkCommandBufferAllocateInfo>& 
        pAllocateInfo, VkCommandBuffer* pCommandBuffers ){
    auto pAllocateInfo_copy = pAllocateInfo;
    for(auto& item : pAllocateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    return vkAllocateCommandBuffers(device,pAllocateInfo_copy.data(),pCommandBuffers);
}
VkResult vkCreateImageView(VkDevice device, const std::vector<VkImageViewCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    return vkCreateImageView(device,pCreateInfo_copy.data(),pAllocator,pView);
}
VkResult vkCreateFence(VkDevice device, const std::vector<VkFenceCreateInfo>& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkFence* pFence ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    return vkCreateFence(device,pCreateInfo_copy.data(),pAllocator,pFence);
}
VkResult vkCreateRenderPass(VkDevice device, const std::vector<VkRenderPassCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    return vkCreateRenderPass(device,pCreateInfo_copy.data(),pAllocator,pRenderPass);
}
void vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const std::vector<VkDebugUtilsLabelEXT>& 
        pLabelInfo ){
    auto pLabelInfo_copy = pLabelInfo;
    for(auto& item : pLabelInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    vkQueueBeginDebugUtilsLabelEXT(queue,pLabelInfo_copy.data());
}
VkResult vkCreateInstance(const std::vector<VkInstanceCreateInfo>& pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkInstance* pInstance ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    return vkCreateInstance(pCreateInfo_copy.data(),pAllocator,pInstance);
}
void vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const std::vector<VkDebugUtilsLabelEXT>& 
        pLabelInfo ){
    auto pLabelInfo_copy = pLabelInfo;
    for(auto& item : pLabelInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    vkCmdInsertDebugUtilsLabelEXT(commandBuffer,pLabelInfo_copy.data());
}
VkResult vkCreatePipelineLayout(VkDevice device, const std::vector<VkPipelineLayoutCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout 
        ){
    auto pCreateInfo_copy = pCreateInfo;
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    return vkCreatePipelineLayout(device,pCreateInfo_copy.data(),pAllocator,pPipelineLayout);
}
void vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const 
        std::vector<VkWriteDescriptorSet>& pDescriptorWrites, uint32_t descriptorCopyCount, 
        const std::vector<VkCopyDescriptorSet>& pDescriptorCopies ){
    auto pDescriptorWrites_copy = pDescriptorWrites;
    for(auto& item : pDescriptorWrites_copy ) item.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    auto pDescriptorCopies_copy = pDescriptorCopies;
    for(auto& item : pDescriptorCopies_copy ) item.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
    vkUpdateDescriptorSets(device,descriptorWriteCount,pDescriptorWrites_copy.data(),descriptorCopyCount,pDescriptorCopies_copy.data());
}
VkResult vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, 
        const std::vector<VkMappedMemoryRange>& pMemoryRanges ){
    auto pMemoryRanges_copy = pMemoryRanges;
    for(auto& item : pMemoryRanges_copy ) item.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    return vkInvalidateMappedMemoryRanges(device,memoryRangeCount,pMemoryRanges_copy.data());
}
VkResult vkAllocateDescriptorSets(VkDevice device, const std::vector<VkDescriptorSetAllocateInfo>& 
        pAllocateInfo, VkDescriptorSet* pDescriptorSets ){
    auto pAllocateInfo_copy = pAllocateInfo;
    for(auto& item : pAllocateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    return vkAllocateDescriptorSets(device,pAllocateInfo_copy.data(),pDescriptorSets);
}
void vkGetImageSubresourceLayout(VkDevice device, VkImage image, const std::initializer_list<VkImageSubresource>& 
        pSubresource, VkSubresourceLayout* pLayout ){
    std::vector<VkImageSubresource> pSubresource_copy{ pSubresource };
    vkGetImageSubresourceLayout(device,image,pSubresource_copy.data(),pLayout);
}
VkResult vkSetDebugUtilsObjectTagEXT(VkDevice device, const std::initializer_list<VkDebugUtilsObjectTagInfoEXT>& 
        pTagInfo ){
    std::vector<VkDebugUtilsObjectTagInfoEXT> pTagInfo_copy{ pTagInfo };
    for(auto& item : pTagInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
    return vkSetDebugUtilsObjectTagEXT(device,pTagInfo_copy.data());
}
void vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT 
        messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const std::initializer_list<VkDebugUtilsMessengerCallbackDataEXT>& 
        pCallbackData ){
    std::vector<VkDebugUtilsMessengerCallbackDataEXT> pCallbackData_copy{ pCallbackData 
        };
    for(auto& item : pCallbackData_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT;
    vkSubmitDebugUtilsMessageEXT(instance,messageSeverity,messageTypes,pCallbackData_copy.data());
}
VkResult vkCreateCommandPool(VkDevice device, const std::initializer_list<VkCommandPoolCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool 
        ){
    std::vector<VkCommandPoolCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    return vkCreateCommandPool(device,pCreateInfo_copy.data(),pAllocator,pCommandPool);
}
void vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const std::initializer_list<VkEvent>& 
        pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, 
        uint32_t memoryBarrierCount, const std::initializer_list<VkMemoryBarrier>& 
        pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const std::initializer_list<VkBufferMemoryBarrier>& 
        pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const std::initializer_list<VkImageMemoryBarrier>& 
        pImageMemoryBarriers ){
    std::vector<VkEvent> pEvents_copy{ pEvents };
    std::vector<VkMemoryBarrier> pMemoryBarriers_copy{ pMemoryBarriers };
    for(auto& item : pMemoryBarriers_copy ) item.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
    std::vector<VkBufferMemoryBarrier> pBufferMemoryBarriers_copy{ pBufferMemoryBarriers 
        };
    for(auto& item : pBufferMemoryBarriers_copy ) item.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    std::vector<VkImageMemoryBarrier> pImageMemoryBarriers_copy{ pImageMemoryBarriers 
        };
    for(auto& item : pImageMemoryBarriers_copy ) item.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    vkCmdWaitEvents(commandBuffer,eventCount,pEvents_copy.data(),srcStageMask,dstStageMask,memoryBarrierCount,pMemoryBarriers_copy.data(),bufferMemoryBarrierCount,pBufferMemoryBarriers_copy.data(),imageMemoryBarrierCount,pImageMemoryBarriers_copy.data());
}
VkResult vkCreateImage(VkDevice device, const std::initializer_list<VkImageCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage ){
    std::vector<VkImageCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    return vkCreateImage(device,pCreateInfo_copy.data(),pAllocator,pImage);
}
void vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const std::initializer_list<VkDebugUtilsLabelEXT>& 
        pLabelInfo ){
    std::vector<VkDebugUtilsLabelEXT> pLabelInfo_copy{ pLabelInfo };
    for(auto& item : pLabelInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    vkCmdBeginDebugUtilsLabelEXT(commandBuffer,pLabelInfo_copy.data());
}
VkResult vkCreateDevice(VkPhysicalDevice physicalDevice, const std::initializer_list<VkDeviceCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice ){
    std::vector<VkDeviceCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    return vkCreateDevice(physicalDevice,pCreateInfo_copy.data(),pAllocator,pDevice);
}
VkResult vkAllocateMemory(VkDevice device, const std::initializer_list<VkMemoryAllocateInfo>& 
        pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory 
        ){
    std::vector<VkMemoryAllocateInfo> pAllocateInfo_copy{ pAllocateInfo };
    for(auto& item : pAllocateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    return vkAllocateMemory(device,pAllocateInfo_copy.data(),pAllocator,pMemory);
}
VkResult vkCreateSwapchainKHR(VkDevice device, const std::initializer_list<VkSwapchainCreateInfoKHR>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain 
        ){
    std::vector<VkSwapchainCreateInfoKHR> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    return vkCreateSwapchainKHR(device,pCreateInfo_copy.data(),pAllocator,pSwapchain);
}
void vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const std::initializer_list<VkRenderPassBeginInfo>& 
        pRenderPassBegin, VkSubpassContents contents ){
    std::vector<VkRenderPassBeginInfo> pRenderPassBegin_copy{ pRenderPassBegin };
    for(auto& item : pRenderPassBegin_copy ) item.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    vkCmdBeginRenderPass(commandBuffer,pRenderPassBegin_copy.data(),contents);
}
VkResult vkCreateBuffer(VkDevice device, const std::initializer_list<VkBufferCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer ){
    std::vector<VkBufferCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    return vkCreateBuffer(device,pCreateInfo_copy.data(),pAllocator,pBuffer);
}
VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance, const std::initializer_list<VkDebugUtilsMessengerCreateInfoEXT>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* 
        pMessenger ){
    std::vector<VkDebugUtilsMessengerCreateInfoEXT> pCreateInfo_copy{ pCreateInfo 
        };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    return vkCreateDebugUtilsMessengerEXT(instance,pCreateInfo_copy.data(),pAllocator,pMessenger);
}
void vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer 
        dstBuffer, uint32_t regionCount, const std::initializer_list<VkBufferCopy>& 
        pRegions ){
    std::vector<VkBufferCopy> pRegions_copy{ pRegions };
    vkCmdCopyBuffer(commandBuffer,srcBuffer,dstBuffer,regionCount,pRegions_copy.data());
}
VkResult vkQueueSubmit(VkQueue queue, uint32_t submitCount, const std::initializer_list<VkSubmitInfo>& 
        pSubmits, VkFence fence ){
    std::vector<VkSubmitInfo> pSubmits_copy{ pSubmits };
    for(auto& item : pSubmits_copy ) item.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    return vkQueueSubmit(queue,submitCount,pSubmits_copy.data(),fence);
}
VkResult vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const std::initializer_list<VkGraphicsPipelineCreateInfo>& 
        pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines 
        ){
    std::vector<VkGraphicsPipelineCreateInfo> pCreateInfos_copy{ pCreateInfos };
    for(auto& item : pCreateInfos_copy ) item.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    return vkCreateGraphicsPipelines(device,pipelineCache,createInfoCount,pCreateInfos_copy.data(),pAllocator,pPipelines);
}
void vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const std::initializer_list<VkClearDepthStencilValue>& pDepthStencil, 
        uint32_t rangeCount, const std::initializer_list<VkImageSubresourceRange>& 
        pRanges ){
    std::vector<VkClearDepthStencilValue> pDepthStencil_copy{ pDepthStencil };
    std::vector<VkImageSubresourceRange> pRanges_copy{ pRanges };
    vkCmdClearDepthStencilImage(commandBuffer,image,imageLayout,pDepthStencil_copy.data(),rangeCount,pRanges_copy.data());
}
VkResult vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const std::initializer_list<VkCommandBufferBeginInfo>& 
        pBeginInfo ){
    std::vector<VkCommandBufferBeginInfo> pBeginInfo_copy{ pBeginInfo };
    for(auto& item : pBeginInfo_copy ) item.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    return vkBeginCommandBuffer(commandBuffer,pBeginInfo_copy.data());
}
void vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, 
        VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t 
        memoryBarrierCount, const std::initializer_list<VkMemoryBarrier>& pMemoryBarriers, 
        uint32_t bufferMemoryBarrierCount, const std::initializer_list<VkBufferMemoryBarrier>& 
        pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const std::initializer_list<VkImageMemoryBarrier>& 
        pImageMemoryBarriers ){
    std::vector<VkMemoryBarrier> pMemoryBarriers_copy{ pMemoryBarriers };
    for(auto& item : pMemoryBarriers_copy ) item.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
    std::vector<VkBufferMemoryBarrier> pBufferMemoryBarriers_copy{ pBufferMemoryBarriers 
        };
    for(auto& item : pBufferMemoryBarriers_copy ) item.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    std::vector<VkImageMemoryBarrier> pImageMemoryBarriers_copy{ pImageMemoryBarriers 
        };
    for(auto& item : pImageMemoryBarriers_copy ) item.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    vkCmdPipelineBarrier(commandBuffer,srcStageMask,dstStageMask,dependencyFlags,memoryBarrierCount,pMemoryBarriers_copy.data(),bufferMemoryBarrierCount,pBufferMemoryBarriers_copy.data(),imageMemoryBarrierCount,pImageMemoryBarriers_copy.data());
}
VkResult vkCreateEvent(VkDevice device, const std::initializer_list<VkEventCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent ){
    std::vector<VkEventCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
    return vkCreateEvent(device,pCreateInfo_copy.data(),pAllocator,pEvent);
}
void vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const std::initializer_list<VkImageCopy>& pRegions ){
    std::vector<VkImageCopy> pRegions_copy{ pRegions };
    vkCmdCopyImage(commandBuffer,srcImage,srcImageLayout,dstImage,dstImageLayout,regionCount,pRegions_copy.data());
}
void vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const std::initializer_list<VkClearColorValue>& pColor, uint32_t 
        rangeCount, const std::initializer_list<VkImageSubresourceRange>& pRanges 
        ){
    std::vector<VkClearColorValue> pColor_copy{ pColor };
    std::vector<VkImageSubresourceRange> pRanges_copy{ pRanges };
    vkCmdClearColorImage(commandBuffer,image,imageLayout,pColor_copy.data(),rangeCount,pRanges_copy.data());
}
VkResult vkEnumerateInstanceExtensionProperties(const std::initializer_list<char>& 
        pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties 
        ){
    std::vector<char> pLayerName_copy{ pLayerName };
    return vkEnumerateInstanceExtensionProperties(pLayerName_copy.data(),pPropertyCount,pProperties);
}
VkResult vkWaitForFences(VkDevice device, uint32_t fenceCount, const std::initializer_list<VkFence>& 
        pFences, VkBool32 waitAll, uint64_t timeout ){
    std::vector<VkFence> pFences_copy{ pFences };
    return vkWaitForFences(device,fenceCount,pFences_copy.data(),waitAll,timeout);
}
VkResult vkSetDebugUtilsObjectNameEXT(VkDevice device, const std::initializer_list<VkDebugUtilsObjectNameInfoEXT>& 
        pNameInfo ){
    std::vector<VkDebugUtilsObjectNameInfoEXT> pNameInfo_copy{ pNameInfo };
    for(auto& item : pNameInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
    return vkSetDebugUtilsObjectNameEXT(device,pNameInfo_copy.data());
}
void vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t 
        viewportCount, const std::initializer_list<VkViewport>& pViewports ){
    std::vector<VkViewport> pViewports_copy{ pViewports };
    vkCmdSetViewport(commandBuffer,firstViewport,viewportCount,pViewports_copy.data());
}
void vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, 
        const std::initializer_list<VkCommandBuffer>& pCommandBuffers ){
    std::vector<VkCommandBuffer> pCommandBuffers_copy{ pCommandBuffers };
    vkFreeCommandBuffers(device,commandPool,commandBufferCount,pCommandBuffers_copy.data());
}
VkResult vkCreateQueryPool(VkDevice device, const std::initializer_list<VkQueryPoolCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool 
        ){
    std::vector<VkQueryPoolCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    return vkCreateQueryPool(device,pCreateInfo_copy.data(),pAllocator,pQueryPool);
}
VkResult vkCreateShaderModule(VkDevice device, const std::initializer_list<VkShaderModuleCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule 
        ){
    std::vector<VkShaderModuleCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    return vkCreateShaderModule(device,pCreateInfo_copy.data(),pAllocator,pShaderModule);
}
VkResult vkCreateFramebuffer(VkDevice device, const std::initializer_list<VkFramebufferCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer 
        ){
    std::vector<VkFramebufferCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    return vkCreateFramebuffer(device,pCreateInfo_copy.data(),pAllocator,pFramebuffer);
}
void vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const std::initializer_list<VkDebugUtilsLabelEXT>& 
        pLabelInfo ){
    std::vector<VkDebugUtilsLabelEXT> pLabelInfo_copy{ pLabelInfo };
    for(auto& item : pLabelInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    vkQueueInsertDebugUtilsLabelEXT(queue,pLabelInfo_copy.data());
}
VkResult vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t 
        srcCacheCount, const std::initializer_list<VkPipelineCache>& pSrcCaches ){
    std::vector<VkPipelineCache> pSrcCaches_copy{ pSrcCaches };
    return vkMergePipelineCaches(device,dstCache,srcCacheCount,pSrcCaches_copy.data());
}
VkResult vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const 
        std::initializer_list<char>& pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* 
        pProperties ){
    std::vector<char> pLayerName_copy{ pLayerName };
    return vkEnumerateDeviceExtensionProperties(physicalDevice,pLayerName_copy.data(),pPropertyCount,pProperties);
}
void vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, 
        const std::initializer_list<VkClearAttachment>& pAttachments, uint32_t rectCount, 
        const std::initializer_list<VkClearRect>& pRects ){
    std::vector<VkClearAttachment> pAttachments_copy{ pAttachments };
    std::vector<VkClearRect> pRects_copy{ pRects };
    vkCmdClearAttachments(commandBuffer,attachmentCount,pAttachments_copy.data(),rectCount,pRects_copy.data());
}
VkResult vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t 
        descriptorSetCount, const std::initializer_list<VkDescriptorSet>& pDescriptorSets 
        ){
    std::vector<VkDescriptorSet> pDescriptorSets_copy{ pDescriptorSets };
    return vkFreeDescriptorSets(device,descriptorPool,descriptorSetCount,pDescriptorSets_copy.data());
}
void vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const std::initializer_list<VkImageResolve>& pRegions ){
    std::vector<VkImageResolve> pRegions_copy{ pRegions };
    vkCmdResolveImage(commandBuffer,srcImage,srcImageLayout,dstImage,dstImageLayout,regionCount,pRegions_copy.data());
}
void vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, 
        const std::initializer_list<VkCommandBuffer>& pCommandBuffers ){
    std::vector<VkCommandBuffer> pCommandBuffers_copy{ pCommandBuffers };
    vkCmdExecuteCommands(commandBuffer,commandBufferCount,pCommandBuffers_copy.data());
}
VkResult vkQueuePresentKHR(VkQueue queue, const std::initializer_list<VkPresentInfoKHR>& 
        pPresentInfo ){
    std::vector<VkPresentInfoKHR> pPresentInfo_copy{ pPresentInfo };
    for(auto& item : pPresentInfo_copy ) item.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    return vkQueuePresentKHR(queue,pPresentInfo_copy.data());
}
void vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage 
        dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const std::initializer_list<VkBufferImageCopy>& 
        pRegions ){
    std::vector<VkBufferImageCopy> pRegions_copy{ pRegions };
    vkCmdCopyBufferToImage(commandBuffer,srcBuffer,dstImage,dstImageLayout,regionCount,pRegions_copy.data());
}
PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance instance, const std::initializer_list<char>& 
        pName ){
    std::vector<char> pName_copy{ pName };
    return vkGetInstanceProcAddr(instance,pName_copy.data());
}
VkResult vkCreateDescriptorSetLayout(VkDevice device, const std::initializer_list<VkDescriptorSetLayoutCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* 
        pSetLayout ){
    std::vector<VkDescriptorSetLayoutCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    return vkCreateDescriptorSetLayout(device,pCreateInfo_copy.data(),pAllocator,pSetLayout);
}
VkResult vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const std::initializer_list<VkComputePipelineCreateInfo>& 
        pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines 
        ){
    std::vector<VkComputePipelineCreateInfo> pCreateInfos_copy{ pCreateInfos };
    for(auto& item : pCreateInfos_copy ) item.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    return vkCreateComputePipelines(device,pipelineCache,createInfoCount,pCreateInfos_copy.data(),pAllocator,pPipelines);
}
void vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t 
        scissorCount, const std::initializer_list<VkRect2D>& pScissors ){
    std::vector<VkRect2D> pScissors_copy{ pScissors };
    vkCmdSetScissor(commandBuffer,firstScissor,scissorCount,pScissors_copy.data());
}
VkResult vkCreateBufferView(VkDevice device, const std::initializer_list<VkBufferViewCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView 
        ){
    std::vector<VkBufferViewCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    return vkCreateBufferView(device,pCreateInfo_copy.data(),pAllocator,pView);
}
void vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, 
        VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, 
        const std::initializer_list<VkDescriptorSet>& pDescriptorSets, uint32_t dynamicOffsetCount, 
        const std::initializer_list<uint32_t>& pDynamicOffsets ){
    std::vector<VkDescriptorSet> pDescriptorSets_copy{ pDescriptorSets };
    std::vector<uint32_t> pDynamicOffsets_copy{ pDynamicOffsets };
    vkCmdBindDescriptorSets(commandBuffer,pipelineBindPoint,layout,firstSet,descriptorSetCount,pDescriptorSets_copy.data(),dynamicOffsetCount,pDynamicOffsets_copy.data());
}
void vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const std::initializer_list<VkImageBlit>& pRegions, VkFilter 
        filter ){
    std::vector<VkImageBlit> pRegions_copy{ pRegions };
    vkCmdBlitImage(commandBuffer,srcImage,srcImageLayout,dstImage,dstImageLayout,regionCount,pRegions_copy.data(),filter);
}
VkResult vkCreateDescriptorPool(VkDevice device, const std::initializer_list<VkDescriptorPoolCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool 
        ){
    std::vector<VkDescriptorPoolCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    return vkCreateDescriptorPool(device,pCreateInfo_copy.data(),pAllocator,pDescriptorPool);
}
VkResult vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const std::initializer_list<VkBindSparseInfo>& 
        pBindInfo, VkFence fence ){
    std::vector<VkBindSparseInfo> pBindInfo_copy{ pBindInfo };
    for(auto& item : pBindInfo_copy ) item.sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO;
    return vkQueueBindSparse(queue,bindInfoCount,pBindInfo_copy.data(),fence);
}
VkResult vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const 
        std::initializer_list<VkMappedMemoryRange>& pMemoryRanges ){
    std::vector<VkMappedMemoryRange> pMemoryRanges_copy{ pMemoryRanges };
    for(auto& item : pMemoryRanges_copy ) item.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    return vkFlushMappedMemoryRanges(device,memoryRangeCount,pMemoryRanges_copy.data());
}
VkResult vkCreateSemaphore(VkDevice device, const std::initializer_list<VkSemaphoreCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore 
        ){
    std::vector<VkSemaphoreCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    return vkCreateSemaphore(device,pCreateInfo_copy.data(),pAllocator,pSemaphore);
}
VkResult vkCreatePipelineCache(VkDevice device, const std::initializer_list<VkPipelineCacheCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache 
        ){
    std::vector<VkPipelineCacheCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    return vkCreatePipelineCache(device,pCreateInfo_copy.data(),pAllocator,pPipelineCache);
}
VkResult vkCreateSampler(VkDevice device, const std::initializer_list<VkSamplerCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler 
        ){
    std::vector<VkSamplerCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    return vkCreateSampler(device,pCreateInfo_copy.data(),pAllocator,pSampler);
}
void vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const std::initializer_list<VkBufferImageCopy>& 
        pRegions ){
    std::vector<VkBufferImageCopy> pRegions_copy{ pRegions };
    vkCmdCopyImageToBuffer(commandBuffer,srcImage,srcImageLayout,dstBuffer,regionCount,pRegions_copy.data());
}
PFN_vkVoidFunction vkGetDeviceProcAddr(VkDevice device, const std::initializer_list<char>& 
        pName ){
    std::vector<char> pName_copy{ pName };
    return vkGetDeviceProcAddr(device,pName_copy.data());
}
VkResult vkAllocateCommandBuffers(VkDevice device, const std::initializer_list<VkCommandBufferAllocateInfo>& 
        pAllocateInfo, VkCommandBuffer* pCommandBuffers ){
    std::vector<VkCommandBufferAllocateInfo> pAllocateInfo_copy{ pAllocateInfo };
    for(auto& item : pAllocateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    return vkAllocateCommandBuffers(device,pAllocateInfo_copy.data(),pCommandBuffers);
}
VkResult vkCreateImageView(VkDevice device, const std::initializer_list<VkImageViewCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView 
        ){
    std::vector<VkImageViewCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    return vkCreateImageView(device,pCreateInfo_copy.data(),pAllocator,pView);
}
void vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, 
        uint32_t bindingCount, const std::initializer_list<VkBuffer>& pBuffers, const 
        std::initializer_list<VkDeviceSize>& pOffsets ){
    std::vector<VkBuffer> pBuffers_copy{ pBuffers };
    std::vector<VkDeviceSize> pOffsets_copy{ pOffsets };
    vkCmdBindVertexBuffers(commandBuffer,firstBinding,bindingCount,pBuffers_copy.data(),pOffsets_copy.data());
}
VkResult vkCreateFence(VkDevice device, const std::initializer_list<VkFenceCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence ){
    std::vector<VkFenceCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    return vkCreateFence(device,pCreateInfo_copy.data(),pAllocator,pFence);
}
VkResult vkCreateRenderPass(VkDevice device, const std::initializer_list<VkRenderPassCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass 
        ){
    std::vector<VkRenderPassCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    return vkCreateRenderPass(device,pCreateInfo_copy.data(),pAllocator,pRenderPass);
}
void vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const std::initializer_list<VkDebugUtilsLabelEXT>& 
        pLabelInfo ){
    std::vector<VkDebugUtilsLabelEXT> pLabelInfo_copy{ pLabelInfo };
    for(auto& item : pLabelInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    vkQueueBeginDebugUtilsLabelEXT(queue,pLabelInfo_copy.data());
}
VkResult vkCreateInstance(const std::initializer_list<VkInstanceCreateInfo>& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkInstance* pInstance ){
    std::vector<VkInstanceCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    return vkCreateInstance(pCreateInfo_copy.data(),pAllocator,pInstance);
}
VkResult vkResetFences(VkDevice device, uint32_t fenceCount, const std::initializer_list<VkFence>& 
        pFences ){
    std::vector<VkFence> pFences_copy{ pFences };
    return vkResetFences(device,fenceCount,pFences_copy.data());
}
void vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const std::initializer_list<VkDebugUtilsLabelEXT>& 
        pLabelInfo ){
    std::vector<VkDebugUtilsLabelEXT> pLabelInfo_copy{ pLabelInfo };
    for(auto& item : pLabelInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    vkCmdInsertDebugUtilsLabelEXT(commandBuffer,pLabelInfo_copy.data());
}
VkResult vkCreatePipelineLayout(VkDevice device, const std::initializer_list<VkPipelineLayoutCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout 
        ){
    std::vector<VkPipelineLayoutCreateInfo> pCreateInfo_copy{ pCreateInfo };
    for(auto& item : pCreateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    return vkCreatePipelineLayout(device,pCreateInfo_copy.data(),pAllocator,pPipelineLayout);
}
void vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const 
        std::initializer_list<VkWriteDescriptorSet>& pDescriptorWrites, uint32_t 
        descriptorCopyCount, const std::initializer_list<VkCopyDescriptorSet>& pDescriptorCopies 
        ){
    std::vector<VkWriteDescriptorSet> pDescriptorWrites_copy{ pDescriptorWrites };
    for(auto& item : pDescriptorWrites_copy ) item.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    std::vector<VkCopyDescriptorSet> pDescriptorCopies_copy{ pDescriptorCopies };
    for(auto& item : pDescriptorCopies_copy ) item.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
    vkUpdateDescriptorSets(device,descriptorWriteCount,pDescriptorWrites_copy.data(),descriptorCopyCount,pDescriptorCopies_copy.data());
}
VkResult vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, 
        const std::initializer_list<VkMappedMemoryRange>& pMemoryRanges ){
    std::vector<VkMappedMemoryRange> pMemoryRanges_copy{ pMemoryRanges };
    for(auto& item : pMemoryRanges_copy ) item.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    return vkInvalidateMappedMemoryRanges(device,memoryRangeCount,pMemoryRanges_copy.data());
}
VkResult vkAllocateDescriptorSets(VkDevice device, const std::initializer_list<VkDescriptorSetAllocateInfo>& 
        pAllocateInfo, VkDescriptorSet* pDescriptorSets ){
    std::vector<VkDescriptorSetAllocateInfo> pAllocateInfo_copy{ pAllocateInfo };
    for(auto& item : pAllocateInfo_copy ) item.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    return vkAllocateDescriptorSets(device,pAllocateInfo_copy.data(),pDescriptorSets);
}
void loadAllVulkanFunctions(VkInstance instance)
{
    _impl_vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout) loadVulkanFunction(instance, 
        "vkGetImageSubresourceLayout");
    _impl_vkDestroyImage = (PFN_vkDestroyImage) loadVulkanFunction(instance, "vkDestroyImage");
    _impl_vkSetDebugUtilsObjectTagEXT = (PFN_vkSetDebugUtilsObjectTagEXT) loadVulkanFunction(instance, 
        "vkSetDebugUtilsObjectTagEXT");
    _impl_vkSubmitDebugUtilsMessageEXT = (PFN_vkSubmitDebugUtilsMessageEXT) loadVulkanFunction(instance, 
        "vkSubmitDebugUtilsMessageEXT");
    _impl_vkCmdDraw = (PFN_vkCmdDraw) loadVulkanFunction(instance, "vkCmdDraw");
    _impl_vkGetFenceStatus = (PFN_vkGetFenceStatus) loadVulkanFunction(instance, 
        "vkGetFenceStatus");
    _impl_vkCreateCommandPool = (PFN_vkCreateCommandPool) loadVulkanFunction(instance, 
        "vkCreateCommandPool");
    _impl_vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements) loadVulkanFunction(instance, 
        "vkGetImageMemoryRequirements");
    _impl_vkCmdWaitEvents = (PFN_vkCmdWaitEvents) loadVulkanFunction(instance, "vkCmdWaitEvents");
    _impl_vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth) loadVulkanFunction(instance, 
        "vkCmdSetLineWidth");
    _impl_vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity) loadVulkanFunction(instance, 
        "vkGetRenderAreaGranularity");
    _impl_vkCreateImage = (PFN_vkCreateImage) loadVulkanFunction(instance, "vkCreateImage");
    _impl_vkCmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT) loadVulkanFunction(instance, 
        "vkCmdBeginDebugUtilsLabelEXT");
    _impl_vkCreateDevice = (PFN_vkCreateDevice) loadVulkanFunction(instance, "vkCreateDevice");
    _impl_vkAllocateMemory = (PFN_vkAllocateMemory) loadVulkanFunction(instance, 
        "vkAllocateMemory");
    _impl_vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR) loadVulkanFunction(instance, 
        "vkCreateSwapchainKHR");
    _impl_vkDestroyRenderPass = (PFN_vkDestroyRenderPass) loadVulkanFunction(instance, 
        "vkDestroyRenderPass");
    _impl_vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference) loadVulkanFunction(instance, 
        "vkCmdSetStencilReference");
    _impl_vkQueueWaitIdle = (PFN_vkQueueWaitIdle) loadVulkanFunction(instance, "vkQueueWaitIdle");
    _impl_vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass) loadVulkanFunction(instance, 
        "vkCmdBeginRenderPass");
    _impl_vkGetEventStatus = (PFN_vkGetEventStatus) loadVulkanFunction(instance, 
        "vkGetEventStatus");
    _impl_vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask) loadVulkanFunction(instance, 
        "vkCmdSetStencilCompareMask");
    _impl_vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect) loadVulkanFunction(instance, 
        "vkCmdDrawIndexedIndirect");
    _impl_vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT) 
        loadVulkanFunction(instance, "vkDestroyDebugUtilsMessengerEXT");
    _impl_vkCreateBuffer = (PFN_vkCreateBuffer) loadVulkanFunction(instance, "vkCreateBuffer");
    _impl_vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT) loadVulkanFunction(instance, 
        "vkCreateDebugUtilsMessengerEXT");
    _impl_vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer) loadVulkanFunction(instance, "vkCmdCopyBuffer");
    _impl_vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer) loadVulkanFunction(instance, 
        "vkCmdUpdateBuffer");
    _impl_vkEndCommandBuffer = (PFN_vkEndCommandBuffer) loadVulkanFunction(instance, 
        "vkEndCommandBuffer");
    _impl_vkResetCommandBuffer = (PFN_vkResetCommandBuffer) loadVulkanFunction(instance, 
        "vkResetCommandBuffer");
    _impl_vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults) loadVulkanFunction(instance, 
        "vkCmdCopyQueryPoolResults");
    _impl_vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties) 
        loadVulkanFunction(instance, "vkGetPhysicalDeviceFormatProperties");
    _impl_vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures) loadVulkanFunction(instance, 
        "vkGetPhysicalDeviceFeatures");
    _impl_vkQueueSubmit = (PFN_vkQueueSubmit) loadVulkanFunction(instance, "vkQueueSubmit");
    _impl_vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines) loadVulkanFunction(instance, 
        "vkCreateGraphicsPipelines");
    _impl_vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties) 
        loadVulkanFunction(instance, "vkGetPhysicalDeviceMemoryProperties");
    _impl_vkGetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties) 
        loadVulkanFunction(instance, "vkGetPhysicalDeviceSparseImageFormatProperties");
    _impl_vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage) loadVulkanFunction(instance, 
        "vkCmdClearDepthStencilImage");
    _impl_vkCmdFillBuffer = (PFN_vkCmdFillBuffer) loadVulkanFunction(instance, "vkCmdFillBuffer");
    _impl_vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer) loadVulkanFunction(instance, 
        "vkBeginCommandBuffer");
    _impl_vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier) loadVulkanFunction(instance, 
        "vkCmdPipelineBarrier");
    _impl_vkFreeMemory = (PFN_vkFreeMemory) loadVulkanFunction(instance, "vkFreeMemory");
    _impl_vkCmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT) loadVulkanFunction(instance, 
        "vkCmdEndDebugUtilsLabelEXT");
    _impl_vkUnmapMemory = (PFN_vkUnmapMemory) loadVulkanFunction(instance, "vkUnmapMemory");
    _impl_vkCreateEvent = (PFN_vkCreateEvent) loadVulkanFunction(instance, "vkCreateEvent");
    _impl_vkCmdCopyImage = (PFN_vkCmdCopyImage) loadVulkanFunction(instance, "vkCmdCopyImage");
    _impl_vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout) loadVulkanFunction(instance, 
        "vkDestroyDescriptorSetLayout");
    _impl_vkDestroyQueryPool = (PFN_vkDestroyQueryPool) loadVulkanFunction(instance, 
        "vkDestroyQueryPool");
    _impl_vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices) loadVulkanFunction(instance, 
        "vkEnumeratePhysicalDevices");
    _impl_vkCmdClearColorImage = (PFN_vkCmdClearColorImage) loadVulkanFunction(instance, 
        "vkCmdClearColorImage");
    _impl_vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties) 
        loadVulkanFunction(instance, "vkEnumerateInstanceExtensionProperties");
    _impl_vkWaitForFences = (PFN_vkWaitForFences) loadVulkanFunction(instance, "vkWaitForFences");
    _impl_vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer) loadVulkanFunction(instance, 
        "vkDestroyFramebuffer");
    _impl_vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties) 
        loadVulkanFunction(instance, "vkEnumerateDeviceLayerProperties");
    _impl_vkCmdBeginQuery = (PFN_vkCmdBeginQuery) loadVulkanFunction(instance, "vkCmdBeginQuery");
    _impl_vkDestroyDevice = (PFN_vkDestroyDevice) loadVulkanFunction(instance, "vkDestroyDevice");
    _impl_vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR) loadVulkanFunction(instance, 
        "vkGetSwapchainImagesKHR");
    _impl_vkDestroyPipeline = (PFN_vkDestroyPipeline) loadVulkanFunction(instance, 
        "vkDestroyPipeline");
    _impl_vkSetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT) loadVulkanFunction(instance, 
        "vkSetDebugUtilsObjectNameEXT");
    _impl_vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties) loadVulkanFunction(instance, 
        "vkGetPhysicalDeviceProperties");
    _impl_vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout) loadVulkanFunction(instance, 
        "vkDestroyPipelineLayout");
    _impl_vkCmdDispatch = (PFN_vkCmdDispatch) loadVulkanFunction(instance, "vkCmdDispatch");
    _impl_vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR) 
        loadVulkanFunction(instance, "vkGetPhysicalDeviceSurfaceSupportKHR");
    _impl_vkCmdSetViewport = (PFN_vkCmdSetViewport) loadVulkanFunction(instance, 
        "vkCmdSetViewport");
    _impl_vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer) loadVulkanFunction(instance, 
        "vkCmdBindIndexBuffer");
    _impl_vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers) loadVulkanFunction(instance, 
        "vkFreeCommandBuffers");
    _impl_vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment) loadVulkanFunction(instance, 
        "vkGetDeviceMemoryCommitment");
    _impl_vkCreateQueryPool = (PFN_vkCreateQueryPool) loadVulkanFunction(instance, 
        "vkCreateQueryPool");
    _impl_vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData) loadVulkanFunction(instance, 
        "vkGetPipelineCacheData");
    _impl_vkDestroyImageView = (PFN_vkDestroyImageView) loadVulkanFunction(instance, 
        "vkDestroyImageView");
    _impl_vkCreateShaderModule = (PFN_vkCreateShaderModule) loadVulkanFunction(instance, 
        "vkCreateShaderModule");
    _impl_vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool) loadVulkanFunction(instance, 
        "vkDestroyDescriptorPool");
    _impl_vkCreateFramebuffer = (PFN_vkCreateFramebuffer) loadVulkanFunction(instance, 
        "vkCreateFramebuffer");
    _impl_vkQueueInsertDebugUtilsLabelEXT = (PFN_vkQueueInsertDebugUtilsLabelEXT) 
        loadVulkanFunction(instance, "vkQueueInsertDebugUtilsLabelEXT");
    _impl_vkCmdResetEvent = (PFN_vkCmdResetEvent) loadVulkanFunction(instance, "vkCmdResetEvent");
    _impl_vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias) loadVulkanFunction(instance, 
        "vkCmdSetDepthBias");
    _impl_vkMapMemory = (PFN_vkMapMemory) loadVulkanFunction(instance, "vkMapMemory");
    _impl_vkGetImageSparseMemoryRequirements = (PFN_vkGetImageSparseMemoryRequirements) 
        loadVulkanFunction(instance, "vkGetImageSparseMemoryRequirements");
    _impl_vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp) loadVulkanFunction(instance, 
        "vkCmdWriteTimestamp");
    _impl_vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache) loadVulkanFunction(instance, 
        "vkDestroyPipelineCache");
    _impl_vkMergePipelineCaches = (PFN_vkMergePipelineCaches) loadVulkanFunction(instance, 
        "vkMergePipelineCaches");
    _impl_vkCmdPushConstants = (PFN_vkCmdPushConstants) loadVulkanFunction(instance, 
        "vkCmdPushConstants");
    _impl_vkCmdBindPipeline = (PFN_vkCmdBindPipeline) loadVulkanFunction(instance, 
        "vkCmdBindPipeline");
    _impl_vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask) loadVulkanFunction(instance, 
        "vkCmdSetStencilWriteMask");
    _impl_vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties) 
        loadVulkanFunction(instance, "vkEnumerateDeviceExtensionProperties");
    _impl_vkCmdClearAttachments = (PFN_vkCmdClearAttachments) loadVulkanFunction(instance, 
        "vkCmdClearAttachments");
    _impl_vkBindBufferMemory = (PFN_vkBindBufferMemory) loadVulkanFunction(instance, 
        "vkBindBufferMemory");
    _impl_vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets) loadVulkanFunction(instance, 
        "vkFreeDescriptorSets");
    _impl_vkCmdResolveImage = (PFN_vkCmdResolveImage) loadVulkanFunction(instance, 
        "vkCmdResolveImage");
    _impl_vkCmdEndQuery = (PFN_vkCmdEndQuery) loadVulkanFunction(instance, "vkCmdEndQuery");
    _impl_vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults) loadVulkanFunction(instance, 
        "vkGetQueryPoolResults");
    _impl_vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands) loadVulkanFunction(instance, 
        "vkCmdExecuteCommands");
    _impl_vkQueuePresentKHR = (PFN_vkQueuePresentKHR) loadVulkanFunction(instance, 
        "vkQueuePresentKHR");
    _impl_vkDestroyBufferView = (PFN_vkDestroyBufferView) loadVulkanFunction(instance, 
        "vkDestroyBufferView");
    _impl_vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties) 
        loadVulkanFunction(instance, "vkEnumerateInstanceLayerProperties");
    _impl_vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage) loadVulkanFunction(instance, 
        "vkCmdCopyBufferToImage");
    _impl_vkDestroyInstance = (PFN_vkDestroyInstance) loadVulkanFunction(instance, 
        "vkDestroyInstance");
    _impl_vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) loadVulkanFunction(instance, 
        "vkGetInstanceProcAddr");
    _impl_vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout) loadVulkanFunction(instance, 
        "vkCreateDescriptorSetLayout");
    _impl_vkCreateComputePipelines = (PFN_vkCreateComputePipelines) loadVulkanFunction(instance, 
        "vkCreateComputePipelines");
    _impl_vkDestroySampler = (PFN_vkDestroySampler) loadVulkanFunction(instance, 
        "vkDestroySampler");
    _impl_vkCmdSetEvent = (PFN_vkCmdSetEvent) loadVulkanFunction(instance, "vkCmdSetEvent");
    _impl_vkCmdNextSubpass = (PFN_vkCmdNextSubpass) loadVulkanFunction(instance, 
        "vkCmdNextSubpass");
    _impl_vkCmdSetScissor = (PFN_vkCmdSetScissor) loadVulkanFunction(instance, "vkCmdSetScissor");
    _impl_vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect) loadVulkanFunction(instance, 
        "vkCmdDrawIndirect");
    _impl_vkCreateBufferView = (PFN_vkCreateBufferView) loadVulkanFunction(instance, 
        "vkCreateBufferView");
    _impl_vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed) loadVulkanFunction(instance, 
        "vkCmdDrawIndexed");
    _impl_vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets) loadVulkanFunction(instance, 
        "vkCmdBindDescriptorSets");
    _impl_vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR) loadVulkanFunction(instance, 
        "vkDestroySwapchainKHR");
    _impl_vkDestroyBuffer = (PFN_vkDestroyBuffer) loadVulkanFunction(instance, "vkDestroyBuffer");
    _impl_vkCmdBlitImage = (PFN_vkCmdBlitImage) loadVulkanFunction(instance, "vkCmdBlitImage");
    _impl_vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR) 
        loadVulkanFunction(instance, "vkGetPhysicalDeviceSurfaceFormatsKHR");
    _impl_vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass) loadVulkanFunction(instance, 
        "vkCmdEndRenderPass");
    _impl_vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool) loadVulkanFunction(instance, 
        "vkCreateDescriptorPool");
    _impl_vkQueueBindSparse = (PFN_vkQueueBindSparse) loadVulkanFunction(instance, 
        "vkQueueBindSparse");
    _impl_vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool) loadVulkanFunction(instance, 
        "vkCmdResetQueryPool");
    _impl_vkGetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties) 
        loadVulkanFunction(instance, "vkGetPhysicalDeviceImageFormatProperties");
    _impl_vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges) loadVulkanFunction(instance, 
        "vkFlushMappedMemoryRanges");
    _impl_vkCreateSemaphore = (PFN_vkCreateSemaphore) loadVulkanFunction(instance, 
        "vkCreateSemaphore");
    _impl_vkDestroyShaderModule = (PFN_vkDestroyShaderModule) loadVulkanFunction(instance, 
        "vkDestroyShaderModule");
    _impl_vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants) loadVulkanFunction(instance, 
        "vkCmdSetBlendConstants");
    _impl_vkCreatePipelineCache = (PFN_vkCreatePipelineCache) loadVulkanFunction(instance, 
        "vkCreatePipelineCache");
    _impl_vkCreateSampler = (PFN_vkCreateSampler) loadVulkanFunction(instance, "vkCreateSampler");
    _impl_vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds) loadVulkanFunction(instance, 
        "vkCmdSetDepthBounds");
    _impl_vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer) loadVulkanFunction(instance, 
        "vkCmdCopyImageToBuffer");
    _impl_vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr) loadVulkanFunction(instance, 
        "vkGetDeviceProcAddr");
    _impl_vkGetDeviceQueue = (PFN_vkGetDeviceQueue) loadVulkanFunction(instance, 
        "vkGetDeviceQueue");
    _impl_vkDestroyEvent = (PFN_vkDestroyEvent) loadVulkanFunction(instance, "vkDestroyEvent");
    _impl_vkResetEvent = (PFN_vkResetEvent) loadVulkanFunction(instance, "vkResetEvent");
    _impl_vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements) loadVulkanFunction(instance, 
        "vkGetBufferMemoryRequirements");
    _impl_vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers) loadVulkanFunction(instance, 
        "vkAllocateCommandBuffers");
    _impl_vkCreateImageView = (PFN_vkCreateImageView) loadVulkanFunction(instance, 
        "vkCreateImageView");
    _impl_vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers) loadVulkanFunction(instance, 
        "vkCmdBindVertexBuffers");
    _impl_vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR) loadVulkanFunction(instance, 
        "vkAcquireNextImageKHR");
    _impl_vkQueueEndDebugUtilsLabelEXT = (PFN_vkQueueEndDebugUtilsLabelEXT) loadVulkanFunction(instance, 
        "vkQueueEndDebugUtilsLabelEXT");
    _impl_vkCreateFence = (PFN_vkCreateFence) loadVulkanFunction(instance, "vkCreateFence");
    _impl_vkCreateRenderPass = (PFN_vkCreateRenderPass) loadVulkanFunction(instance, 
        "vkCreateRenderPass");
    _impl_vkDestroySemaphore = (PFN_vkDestroySemaphore) loadVulkanFunction(instance, 
        "vkDestroySemaphore");
    _impl_vkQueueBeginDebugUtilsLabelEXT = (PFN_vkQueueBeginDebugUtilsLabelEXT) loadVulkanFunction(instance, 
        "vkQueueBeginDebugUtilsLabelEXT");
    _impl_vkBindImageMemory = (PFN_vkBindImageMemory) loadVulkanFunction(instance, 
        "vkBindImageMemory");
    _impl_vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR) 
        loadVulkanFunction(instance, "vkGetPhysicalDeviceSurfacePresentModesKHR");
    _impl_vkCreateInstance = (PFN_vkCreateInstance) loadVulkanFunction(instance, 
        "vkCreateInstance");
    _impl_vkDestroyFence = (PFN_vkDestroyFence) loadVulkanFunction(instance, "vkDestroyFence");
    _impl_vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle) loadVulkanFunction(instance, 
        "vkDeviceWaitIdle");
    _impl_vkResetFences = (PFN_vkResetFences) loadVulkanFunction(instance, "vkResetFences");
    _impl_vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR) loadVulkanFunction(instance, 
        "vkDestroySurfaceKHR");
    _impl_vkCmdInsertDebugUtilsLabelEXT = (PFN_vkCmdInsertDebugUtilsLabelEXT) loadVulkanFunction(instance, 
        "vkCmdInsertDebugUtilsLabelEXT");
    _impl_vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout) loadVulkanFunction(instance, 
        "vkCreatePipelineLayout");
    _impl_vkSetEvent = (PFN_vkSetEvent) loadVulkanFunction(instance, "vkSetEvent");
    _impl_vkDestroyCommandPool = (PFN_vkDestroyCommandPool) loadVulkanFunction(instance, 
        "vkDestroyCommandPool");
    _impl_vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets) loadVulkanFunction(instance, 
        "vkUpdateDescriptorSets");
    _impl_vkResetCommandPool = (PFN_vkResetCommandPool) loadVulkanFunction(instance, 
        "vkResetCommandPool");
    _impl_vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect) loadVulkanFunction(instance, 
        "vkCmdDispatchIndirect");
    _impl_vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges) loadVulkanFunction(instance, 
        "vkInvalidateMappedMemoryRanges");
    _impl_vkResetDescriptorPool = (PFN_vkResetDescriptorPool) loadVulkanFunction(instance, 
        "vkResetDescriptorPool");
    _impl_vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets) loadVulkanFunction(instance, 
        "vkAllocateDescriptorSets");
    _impl_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) 
        loadVulkanFunction(instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
    _impl_vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties) 
        loadVulkanFunction(instance, "vkGetPhysicalDeviceQueueFamilyProperties");
}
