//Generated from vk.xml, which has this copyright:
// 
// Copyright 2015-2022 The Khronos Group Inc.
// 
// SPDX-License-Identifier: Apache-2.0 OR MIT
// 

#pragma once
#ifdef VK_HEADER_VERSION
#error You must include vk.h before including vulkan.h
#endif
#define VK_NO_PROTOTYPES 1
#include <vulkan/vulkan.h>
#include <vector>
void loadAllVulkanFunctions(VkInstance instance);
void loadSpecialVulkanFunctions();
void vkGetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* 
        pSubresource, VkSubresourceLayout* pLayout );
void vkDestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* 
        pAllocator );
VkResult vkSetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* 
        pTagInfo );
void vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT 
        messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* 
        pCallbackData );
void vkCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, 
        uint32_t firstVertex, uint32_t firstInstance );
VkResult vkGetFenceStatus(VkDevice device, VkFence fence );
VkResult vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool );
void vkGetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* 
        pMemoryRequirements );
void vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* 
        pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, 
        uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t 
        bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, 
        uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers 
        );
void vkCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth );
void vkGetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* 
        pGranularity );
VkResult vkCreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkImage* pImage );
void vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* 
        pLabelInfo );
VkResult vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice );
VkResult vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, 
        const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory );
VkResult vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain );
void vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* 
        pAllocator );
void vkCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, 
        uint32_t reference );
VkResult vkQueueWaitIdle(VkQueue queue );
void vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* 
        pRenderPassBegin, VkSubpassContents contents );
VkResult vkGetEventStatus(VkDevice device, VkEvent event );
void vkCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags 
        faceMask, uint32_t compareMask );
void vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize 
        offset, uint32_t drawCount, uint32_t stride );
void vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT 
        messenger, const VkAllocationCallbacks* pAllocator );
VkResult vkCreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer );
VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* 
        pMessenger );
void vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer 
        dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions );
void vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize 
        dstOffset, VkDeviceSize dataSize, const void* pData );
VkResult vkEndCommandBuffer(VkCommandBuffer commandBuffer );
VkResult vkResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags 
        flags );
void vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, 
        uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize 
        dstOffset, VkDeviceSize stride, VkQueryResultFlags flags );
void vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat 
        format, VkFormatProperties* pFormatProperties );
void vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* 
        pFeatures );
VkResult vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, 
        VkFence fence );
VkResult vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, 
        const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines );
void vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* 
        pMemoryProperties );
void vkGetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, 
        VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags 
        usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* 
        pProperties );
void vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, 
        const VkImageSubresourceRange* pRanges );
void vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize 
        dstOffset, VkDeviceSize size, uint32_t data );
VkResult vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* 
        pBeginInfo );
void vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, 
        VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t 
        memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, 
        const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, 
        const VkImageMemoryBarrier* pImageMemoryBarriers );
void vkFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* 
        pAllocator );
void vkCmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer );
void vkUnmapMemory(VkDevice device, VkDeviceMemory memory );
VkResult vkCreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkEvent* pEvent );
void vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const VkImageCopy* pRegions );
void vkDestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, 
        const VkAllocationCallbacks* pAllocator );
void vkDestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* 
        pAllocator );
VkResult vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, 
        VkPhysicalDevice* pPhysicalDevices );
void vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const 
        VkImageSubresourceRange* pRanges );
VkResult vkEnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* 
        pPropertyCount, VkExtensionProperties* pProperties );
VkResult vkWaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, 
        VkBool32 waitAll, uint64_t timeout );
void vkDestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* 
        pAllocator );
VkResult vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* 
        pPropertyCount, VkLayerProperties* pProperties );
void vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t 
        query, VkQueryControlFlags flags );
void vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator );
VkResult vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* 
        pSwapchainImageCount, VkImage* pSwapchainImages );
void vkDestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* 
        pAllocator );
VkResult vkSetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* 
        pNameInfo );
void vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* 
        pProperties );
void vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const 
        VkAllocationCallbacks* pAllocator );
void vkCmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t 
        groupCountY, uint32_t groupCountZ );
VkResult vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t 
        queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported );
void vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t 
        viewportCount, const VkViewport* pViewports );
void vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize 
        offset, VkIndexType indexType );
void vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, 
        const VkCommandBuffer* pCommandBuffers );
void vkGetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* 
        pCommittedMemoryInBytes );
VkResult vkCreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool );
VkResult vkGetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* 
        pDataSize, void* pData );
void vkDestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* 
        pAllocator );
VkResult vkCreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule );
void vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const 
        VkAllocationCallbacks* pAllocator );
VkResult vkCreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer );
void vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo 
        );
void vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags 
        stageMask );
void vkCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, 
        float depthBiasClamp, float depthBiasSlopeFactor );
VkResult vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, 
        VkDeviceSize size, VkMemoryMapFlags flags, void** ppData );
void vkGetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* 
        pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements 
        );
void vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, 
        VkQueryPool queryPool, uint32_t query );
void vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const 
        VkAllocationCallbacks* pAllocator );
VkResult vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t 
        srcCacheCount, const VkPipelineCache* pSrcCaches );
void vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags 
        stageFlags, uint32_t offset, uint32_t size, const void* pValues );
void vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, 
        VkPipeline pipeline );
void vkCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, 
        uint32_t writeMask );
VkResult vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const 
        char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties 
        );
void vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, 
        const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* 
        pRects );
VkResult vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, 
        VkDeviceSize memoryOffset );
VkResult vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t 
        descriptorSetCount, const VkDescriptorSet* pDescriptorSets );
void vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const VkImageResolve* pRegions );
void vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t 
        query );
VkResult vkGetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, 
        uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags 
        flags );
void vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, 
        const VkCommandBuffer* pCommandBuffers );
VkResult vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo );
void vkDestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* 
        pAllocator );
VkResult vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* 
        pProperties );
void vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage 
        dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* 
        pRegions );
void vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator 
        );
PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance instance, const char* pName );
VkResult vkCreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* 
        pSetLayout );
VkResult vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, 
        const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines );
void vkDestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* 
        pAllocator );
void vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags 
        stageMask );
void vkCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents );
void vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t 
        scissorCount, const VkRect2D* pScissors );
void vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize 
        offset, uint32_t drawCount, uint32_t stride );
VkResult vkCreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkBufferView* pView );
void vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t 
        instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance 
        );
void vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, 
        VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, 
        const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const 
        uint32_t* pDynamicOffsets );
void vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* 
        pAllocator );
void vkDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* 
        pAllocator );
void vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const VkImageBlit* pRegions, VkFilter filter );
VkResult vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR 
        surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats 
        );
void vkCmdEndRenderPass(VkCommandBuffer commandBuffer );
VkResult vkCreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool 
        );
VkResult vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* 
        pBindInfo, VkFence fence );
void vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t 
        firstQuery, uint32_t queryCount );
VkResult vkGetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, 
        VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags 
        usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties 
        );
VkResult vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const 
        VkMappedMemoryRange* pMemoryRanges );
VkResult vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore );
void vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* 
        pAllocator );
void vkCmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4] 
        );
VkResult vkCreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache 
        );
VkResult vkCreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkSampler* pSampler );
void vkCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float 
        maxDepthBounds );
void vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* 
        pRegions );
PFN_vkVoidFunction vkGetDeviceProcAddr(VkDevice device, const char* pName );
void vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, 
        VkQueue* pQueue );
void vkDestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* 
        pAllocator );
VkResult vkResetEvent(VkDevice device, VkEvent event );
void vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* 
        pMemoryRequirements );
VkResult vkAllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* 
        pAllocateInfo, VkCommandBuffer* pCommandBuffers );
VkResult vkCreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkImageView* pView );
void vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, 
        uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets 
        );
VkResult vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t 
        timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex );
void vkQueueEndDebugUtilsLabelEXT(VkQueue queue );
VkResult vkCreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkFence* pFence );
VkResult vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass );
void vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* 
        pAllocator );
void vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo 
        );
VkResult vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, 
        VkDeviceSize memoryOffset );
VkResult vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, 
        VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes 
        );
VkResult vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* 
        pAllocator, VkInstance* pInstance );
void vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* 
        pAllocator );
VkResult vkDeviceWaitIdle(VkDevice device );
VkResult vkResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences 
        );
void vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* 
        pAllocator );
void vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* 
        pLabelInfo );
VkResult vkCreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout 
        );
VkResult vkSetEvent(VkDevice device, VkEvent event );
void vkDestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* 
        pAllocator );
void vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const 
        VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const 
        VkCopyDescriptorSet* pDescriptorCopies );
VkResult vkResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags 
        flags );
void vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize 
        offset );
VkResult vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, 
        const VkMappedMemoryRange* pMemoryRanges );
VkResult vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, 
        VkDescriptorPoolResetFlags flags );
VkResult vkAllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* 
        pAllocateInfo, VkDescriptorSet* pDescriptorSets );
VkResult vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, 
        VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities );
void vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* 
        pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties 
        );
void vkGetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource& 
        pSubresource, VkSubresourceLayout* pLayout );
VkResult vkSetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT& 
        pTagInfo );
void vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT 
        messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT& 
        pCallbackData );
VkResult vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool );
void vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* 
        pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, 
        uint32_t memoryBarrierCount, const VkMemoryBarrier& pMemoryBarriers, uint32_t 
        bufferMemoryBarrierCount, const VkBufferMemoryBarrier& pBufferMemoryBarriers, 
        uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier& pImageMemoryBarriers 
        );
VkResult vkCreateImage(VkDevice device, const VkImageCreateInfo& pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkImage* pImage );
void vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT& 
        pLabelInfo );
VkResult vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice );
VkResult vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo& pAllocateInfo, 
        const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory );
VkResult vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain );
void vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo& 
        pRenderPassBegin, VkSubpassContents contents );
VkResult vkCreateBuffer(VkDevice device, const VkBufferCreateInfo& pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer );
VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* 
        pMessenger );
void vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer 
        dstBuffer, uint32_t regionCount, const VkBufferCopy& pRegions );
VkResult vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo& pSubmits, 
        VkFence fence );
VkResult vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo& pCreateInfos, 
        const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines );
void vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const VkClearDepthStencilValue& pDepthStencil, uint32_t rangeCount, 
        const VkImageSubresourceRange& pRanges );
VkResult vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo& 
        pBeginInfo );
void vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, 
        VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t 
        memoryBarrierCount, const VkMemoryBarrier& pMemoryBarriers, uint32_t bufferMemoryBarrierCount, 
        const VkBufferMemoryBarrier& pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, 
        const VkImageMemoryBarrier& pImageMemoryBarriers );
VkResult vkCreateEvent(VkDevice device, const VkEventCreateInfo& pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkEvent* pEvent );
void vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const VkImageCopy& pRegions );
void vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const VkClearColorValue& pColor, uint32_t rangeCount, const 
        VkImageSubresourceRange& pRanges );
VkResult vkSetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT& 
        pNameInfo );
void vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t 
        viewportCount, const VkViewport& pViewports );
VkResult vkCreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool );
VkResult vkCreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule );
VkResult vkCreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer );
void vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT& pLabelInfo 
        );
void vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, 
        const VkClearAttachment& pAttachments, uint32_t rectCount, const VkClearRect& 
        pRects );
void vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const VkImageResolve& pRegions );
VkResult vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR& pPresentInfo );
void vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage 
        dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy& 
        pRegions );
VkResult vkCreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* 
        pSetLayout );
VkResult vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const VkComputePipelineCreateInfo& pCreateInfos, 
        const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines );
void vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t 
        scissorCount, const VkRect2D& pScissors );
VkResult vkCreateBufferView(VkDevice device, const VkBufferViewCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkBufferView* pView );
void vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const VkImageBlit& pRegions, VkFilter filter );
VkResult vkCreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool 
        );
VkResult vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo& 
        pBindInfo, VkFence fence );
VkResult vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const 
        VkMappedMemoryRange& pMemoryRanges );
VkResult vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore );
VkResult vkCreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache 
        );
VkResult vkCreateSampler(VkDevice device, const VkSamplerCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkSampler* pSampler );
void vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy& 
        pRegions );
VkResult vkAllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo& 
        pAllocateInfo, VkCommandBuffer* pCommandBuffers );
VkResult vkCreateImageView(VkDevice device, const VkImageViewCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkImageView* pView );
VkResult vkCreateFence(VkDevice device, const VkFenceCreateInfo& pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkFence* pFence );
VkResult vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass );
void vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT& pLabelInfo 
        );
VkResult vkCreateInstance(const VkInstanceCreateInfo& pCreateInfo, const VkAllocationCallbacks* 
        pAllocator, VkInstance* pInstance );
void vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT& 
        pLabelInfo );
VkResult vkCreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout 
        );
void vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const 
        VkWriteDescriptorSet& pDescriptorWrites, uint32_t descriptorCopyCount, const 
        VkCopyDescriptorSet& pDescriptorCopies );
VkResult vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, 
        const VkMappedMemoryRange& pMemoryRanges );
VkResult vkAllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo& 
        pAllocateInfo, VkDescriptorSet* pDescriptorSets );
void vkGetImageSubresourceLayout(VkDevice device, VkImage image, const std::vector<VkImageSubresource>& 
        pSubresource, VkSubresourceLayout* pLayout );
VkResult vkSetDebugUtilsObjectTagEXT(VkDevice device, const std::vector<VkDebugUtilsObjectTagInfoEXT>& 
        pTagInfo );
void vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT 
        messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const std::vector<VkDebugUtilsMessengerCallbackDataEXT>& 
        pCallbackData );
VkResult vkCreateCommandPool(VkDevice device, const std::vector<VkCommandPoolCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool 
        );
void vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* 
        pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, 
        uint32_t memoryBarrierCount, const std::vector<VkMemoryBarrier>& pMemoryBarriers, 
        uint32_t bufferMemoryBarrierCount, const std::vector<VkBufferMemoryBarrier>& 
        pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const std::vector<VkImageMemoryBarrier>& 
        pImageMemoryBarriers );
VkResult vkCreateImage(VkDevice device, const std::vector<VkImageCreateInfo>& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkImage* pImage );
void vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const std::vector<VkDebugUtilsLabelEXT>& 
        pLabelInfo );
VkResult vkCreateDevice(VkPhysicalDevice physicalDevice, const std::vector<VkDeviceCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice );
VkResult vkAllocateMemory(VkDevice device, const std::vector<VkMemoryAllocateInfo>& 
        pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory 
        );
VkResult vkCreateSwapchainKHR(VkDevice device, const std::vector<VkSwapchainCreateInfoKHR>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain 
        );
void vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const std::vector<VkRenderPassBeginInfo>& 
        pRenderPassBegin, VkSubpassContents contents );
VkResult vkCreateBuffer(VkDevice device, const std::vector<VkBufferCreateInfo>& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer );
VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance, const std::vector<VkDebugUtilsMessengerCreateInfoEXT>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* 
        pMessenger );
void vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer 
        dstBuffer, uint32_t regionCount, const std::vector<VkBufferCopy>& pRegions 
        );
VkResult vkQueueSubmit(VkQueue queue, uint32_t submitCount, const std::vector<VkSubmitInfo>& 
        pSubmits, VkFence fence );
VkResult vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const std::vector<VkGraphicsPipelineCreateInfo>& 
        pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines 
        );
void vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const std::vector<VkClearDepthStencilValue>& pDepthStencil, 
        uint32_t rangeCount, const std::vector<VkImageSubresourceRange>& pRanges 
        );
VkResult vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const std::vector<VkCommandBufferBeginInfo>& 
        pBeginInfo );
void vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, 
        VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t 
        memoryBarrierCount, const std::vector<VkMemoryBarrier>& pMemoryBarriers, 
        uint32_t bufferMemoryBarrierCount, const std::vector<VkBufferMemoryBarrier>& 
        pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const std::vector<VkImageMemoryBarrier>& 
        pImageMemoryBarriers );
VkResult vkCreateEvent(VkDevice device, const std::vector<VkEventCreateInfo>& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkEvent* pEvent );
void vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const std::vector<VkImageCopy>& pRegions );
void vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const std::vector<VkClearColorValue>& pColor, uint32_t rangeCount, 
        const std::vector<VkImageSubresourceRange>& pRanges );
VkResult vkSetDebugUtilsObjectNameEXT(VkDevice device, const std::vector<VkDebugUtilsObjectNameInfoEXT>& 
        pNameInfo );
void vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t 
        viewportCount, const std::vector<VkViewport>& pViewports );
VkResult vkCreateQueryPool(VkDevice device, const std::vector<VkQueryPoolCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool 
        );
VkResult vkCreateShaderModule(VkDevice device, const std::vector<VkShaderModuleCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule 
        );
VkResult vkCreateFramebuffer(VkDevice device, const std::vector<VkFramebufferCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer 
        );
void vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const std::vector<VkDebugUtilsLabelEXT>& 
        pLabelInfo );
void vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, 
        const std::vector<VkClearAttachment>& pAttachments, uint32_t rectCount, const 
        std::vector<VkClearRect>& pRects );
void vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const std::vector<VkImageResolve>& pRegions );
VkResult vkQueuePresentKHR(VkQueue queue, const std::vector<VkPresentInfoKHR>& pPresentInfo 
        );
void vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage 
        dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const std::vector<VkBufferImageCopy>& 
        pRegions );
VkResult vkCreateDescriptorSetLayout(VkDevice device, const std::vector<VkDescriptorSetLayoutCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* 
        pSetLayout );
VkResult vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const std::vector<VkComputePipelineCreateInfo>& 
        pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines 
        );
void vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t 
        scissorCount, const std::vector<VkRect2D>& pScissors );
VkResult vkCreateBufferView(VkDevice device, const std::vector<VkBufferViewCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView 
        );
void vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const std::vector<VkImageBlit>& pRegions, VkFilter filter );
VkResult vkCreateDescriptorPool(VkDevice device, const std::vector<VkDescriptorPoolCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool 
        );
VkResult vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const std::vector<VkBindSparseInfo>& 
        pBindInfo, VkFence fence );
VkResult vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const 
        std::vector<VkMappedMemoryRange>& pMemoryRanges );
VkResult vkCreateSemaphore(VkDevice device, const std::vector<VkSemaphoreCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore 
        );
VkResult vkCreatePipelineCache(VkDevice device, const std::vector<VkPipelineCacheCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache 
        );
VkResult vkCreateSampler(VkDevice device, const std::vector<VkSamplerCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler 
        );
void vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const std::vector<VkBufferImageCopy>& 
        pRegions );
VkResult vkAllocateCommandBuffers(VkDevice device, const std::vector<VkCommandBufferAllocateInfo>& 
        pAllocateInfo, VkCommandBuffer* pCommandBuffers );
VkResult vkCreateImageView(VkDevice device, const std::vector<VkImageViewCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView 
        );
VkResult vkCreateFence(VkDevice device, const std::vector<VkFenceCreateInfo>& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkFence* pFence );
VkResult vkCreateRenderPass(VkDevice device, const std::vector<VkRenderPassCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass 
        );
void vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const std::vector<VkDebugUtilsLabelEXT>& 
        pLabelInfo );
VkResult vkCreateInstance(const std::vector<VkInstanceCreateInfo>& pCreateInfo, const 
        VkAllocationCallbacks* pAllocator, VkInstance* pInstance );
void vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const std::vector<VkDebugUtilsLabelEXT>& 
        pLabelInfo );
VkResult vkCreatePipelineLayout(VkDevice device, const std::vector<VkPipelineLayoutCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout 
        );
void vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const 
        std::vector<VkWriteDescriptorSet>& pDescriptorWrites, uint32_t descriptorCopyCount, 
        const std::vector<VkCopyDescriptorSet>& pDescriptorCopies );
VkResult vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, 
        const std::vector<VkMappedMemoryRange>& pMemoryRanges );
VkResult vkAllocateDescriptorSets(VkDevice device, const std::vector<VkDescriptorSetAllocateInfo>& 
        pAllocateInfo, VkDescriptorSet* pDescriptorSets );
void vkGetImageSubresourceLayout(VkDevice device, VkImage image, const std::initializer_list<VkImageSubresource>& 
        pSubresource, VkSubresourceLayout* pLayout );
VkResult vkSetDebugUtilsObjectTagEXT(VkDevice device, const std::initializer_list<VkDebugUtilsObjectTagInfoEXT>& 
        pTagInfo );
void vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT 
        messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const std::initializer_list<VkDebugUtilsMessengerCallbackDataEXT>& 
        pCallbackData );
VkResult vkCreateCommandPool(VkDevice device, const std::initializer_list<VkCommandPoolCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool 
        );
void vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const std::initializer_list<VkEvent>& 
        pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, 
        uint32_t memoryBarrierCount, const std::initializer_list<VkMemoryBarrier>& 
        pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const std::initializer_list<VkBufferMemoryBarrier>& 
        pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const std::initializer_list<VkImageMemoryBarrier>& 
        pImageMemoryBarriers );
VkResult vkCreateImage(VkDevice device, const std::initializer_list<VkImageCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage );
void vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const std::initializer_list<VkDebugUtilsLabelEXT>& 
        pLabelInfo );
VkResult vkCreateDevice(VkPhysicalDevice physicalDevice, const std::initializer_list<VkDeviceCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice );
VkResult vkAllocateMemory(VkDevice device, const std::initializer_list<VkMemoryAllocateInfo>& 
        pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory 
        );
VkResult vkCreateSwapchainKHR(VkDevice device, const std::initializer_list<VkSwapchainCreateInfoKHR>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain 
        );
void vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const std::initializer_list<VkRenderPassBeginInfo>& 
        pRenderPassBegin, VkSubpassContents contents );
VkResult vkCreateBuffer(VkDevice device, const std::initializer_list<VkBufferCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer );
VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance, const std::initializer_list<VkDebugUtilsMessengerCreateInfoEXT>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* 
        pMessenger );
void vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer 
        dstBuffer, uint32_t regionCount, const std::initializer_list<VkBufferCopy>& 
        pRegions );
VkResult vkQueueSubmit(VkQueue queue, uint32_t submitCount, const std::initializer_list<VkSubmitInfo>& 
        pSubmits, VkFence fence );
VkResult vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const std::initializer_list<VkGraphicsPipelineCreateInfo>& 
        pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines 
        );
void vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const std::initializer_list<VkClearDepthStencilValue>& pDepthStencil, 
        uint32_t rangeCount, const std::initializer_list<VkImageSubresourceRange>& 
        pRanges );
VkResult vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const std::initializer_list<VkCommandBufferBeginInfo>& 
        pBeginInfo );
void vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, 
        VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t 
        memoryBarrierCount, const std::initializer_list<VkMemoryBarrier>& pMemoryBarriers, 
        uint32_t bufferMemoryBarrierCount, const std::initializer_list<VkBufferMemoryBarrier>& 
        pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const std::initializer_list<VkImageMemoryBarrier>& 
        pImageMemoryBarriers );
VkResult vkCreateEvent(VkDevice device, const std::initializer_list<VkEventCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent );
void vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const std::initializer_list<VkImageCopy>& pRegions );
void vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout 
        imageLayout, const std::initializer_list<VkClearColorValue>& pColor, uint32_t 
        rangeCount, const std::initializer_list<VkImageSubresourceRange>& pRanges 
        );
VkResult vkEnumerateInstanceExtensionProperties(const std::initializer_list<char>& 
        pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties 
        );
VkResult vkWaitForFences(VkDevice device, uint32_t fenceCount, const std::initializer_list<VkFence>& 
        pFences, VkBool32 waitAll, uint64_t timeout );
VkResult vkSetDebugUtilsObjectNameEXT(VkDevice device, const std::initializer_list<VkDebugUtilsObjectNameInfoEXT>& 
        pNameInfo );
void vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t 
        viewportCount, const std::initializer_list<VkViewport>& pViewports );
void vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, 
        const std::initializer_list<VkCommandBuffer>& pCommandBuffers );
VkResult vkCreateQueryPool(VkDevice device, const std::initializer_list<VkQueryPoolCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool 
        );
VkResult vkCreateShaderModule(VkDevice device, const std::initializer_list<VkShaderModuleCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule 
        );
VkResult vkCreateFramebuffer(VkDevice device, const std::initializer_list<VkFramebufferCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer 
        );
void vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const std::initializer_list<VkDebugUtilsLabelEXT>& 
        pLabelInfo );
VkResult vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t 
        srcCacheCount, const std::initializer_list<VkPipelineCache>& pSrcCaches );
VkResult vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const 
        std::initializer_list<char>& pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* 
        pProperties );
void vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, 
        const std::initializer_list<VkClearAttachment>& pAttachments, uint32_t rectCount, 
        const std::initializer_list<VkClearRect>& pRects );
VkResult vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t 
        descriptorSetCount, const std::initializer_list<VkDescriptorSet>& pDescriptorSets 
        );
void vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const std::initializer_list<VkImageResolve>& pRegions );
void vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, 
        const std::initializer_list<VkCommandBuffer>& pCommandBuffers );
VkResult vkQueuePresentKHR(VkQueue queue, const std::initializer_list<VkPresentInfoKHR>& 
        pPresentInfo );
void vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage 
        dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const std::initializer_list<VkBufferImageCopy>& 
        pRegions );
PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance instance, const std::initializer_list<char>& 
        pName );
VkResult vkCreateDescriptorSetLayout(VkDevice device, const std::initializer_list<VkDescriptorSetLayoutCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* 
        pSetLayout );
VkResult vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, 
        uint32_t createInfoCount, const std::initializer_list<VkComputePipelineCreateInfo>& 
        pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines 
        );
void vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t 
        scissorCount, const std::initializer_list<VkRect2D>& pScissors );
VkResult vkCreateBufferView(VkDevice device, const std::initializer_list<VkBufferViewCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView 
        );
void vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, 
        VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, 
        const std::initializer_list<VkDescriptorSet>& pDescriptorSets, uint32_t dynamicOffsetCount, 
        const std::initializer_list<uint32_t>& pDynamicOffsets );
void vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t 
        regionCount, const std::initializer_list<VkImageBlit>& pRegions, VkFilter 
        filter );
VkResult vkCreateDescriptorPool(VkDevice device, const std::initializer_list<VkDescriptorPoolCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool 
        );
VkResult vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const std::initializer_list<VkBindSparseInfo>& 
        pBindInfo, VkFence fence );
VkResult vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const 
        std::initializer_list<VkMappedMemoryRange>& pMemoryRanges );
VkResult vkCreateSemaphore(VkDevice device, const std::initializer_list<VkSemaphoreCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore 
        );
VkResult vkCreatePipelineCache(VkDevice device, const std::initializer_list<VkPipelineCacheCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache 
        );
VkResult vkCreateSampler(VkDevice device, const std::initializer_list<VkSamplerCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler 
        );
void vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout 
        srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const std::initializer_list<VkBufferImageCopy>& 
        pRegions );
PFN_vkVoidFunction vkGetDeviceProcAddr(VkDevice device, const std::initializer_list<char>& 
        pName );
VkResult vkAllocateCommandBuffers(VkDevice device, const std::initializer_list<VkCommandBufferAllocateInfo>& 
        pAllocateInfo, VkCommandBuffer* pCommandBuffers );
VkResult vkCreateImageView(VkDevice device, const std::initializer_list<VkImageViewCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView 
        );
void vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, 
        uint32_t bindingCount, const std::initializer_list<VkBuffer>& pBuffers, const 
        std::initializer_list<VkDeviceSize>& pOffsets );
VkResult vkCreateFence(VkDevice device, const std::initializer_list<VkFenceCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence );
VkResult vkCreateRenderPass(VkDevice device, const std::initializer_list<VkRenderPassCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass 
        );
void vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const std::initializer_list<VkDebugUtilsLabelEXT>& 
        pLabelInfo );
VkResult vkCreateInstance(const std::initializer_list<VkInstanceCreateInfo>& pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, VkInstance* pInstance );
VkResult vkResetFences(VkDevice device, uint32_t fenceCount, const std::initializer_list<VkFence>& 
        pFences );
void vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const std::initializer_list<VkDebugUtilsLabelEXT>& 
        pLabelInfo );
VkResult vkCreatePipelineLayout(VkDevice device, const std::initializer_list<VkPipelineLayoutCreateInfo>& 
        pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout 
        );
void vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const 
        std::initializer_list<VkWriteDescriptorSet>& pDescriptorWrites, uint32_t 
        descriptorCopyCount, const std::initializer_list<VkCopyDescriptorSet>& pDescriptorCopies 
        );
VkResult vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, 
        const std::initializer_list<VkMappedMemoryRange>& pMemoryRanges );
VkResult vkAllocateDescriptorSets(VkDevice device, const std::initializer_list<VkDescriptorSetAllocateInfo>& 
        pAllocateInfo, VkDescriptorSet* pDescriptorSets );
