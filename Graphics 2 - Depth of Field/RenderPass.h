#pragma once
#include "vkhelpers.h"

/// Holds information about a renderpass.
class RenderPass{
  public:
  
    /// The renderpass itself
    VkRenderPass renderPass;
    
    /// Associated context
    VulkanContext* ctx;
    
    /// For debugging
    std::string name;
    
    /// Number of layers in the render target
    int numLayers;
    
    /// Renderpass for the window
    /// @param ctx Associated context
    /// @param startingOp How the framebuffer contents should be treated
    ///     at the start of the renderpass.
    RenderPass(VulkanContext* ctx, VkAttachmentLoadOp startingOp);
    
    /// Renderpass for an offscreen image
    /// @param ctx Associated context
    /// @param colorFormat Format of image
    /// @param numLayers Number of layers
    /// @param depthFormat Depth buffer format
    /// @param finalLayoutColor Image layout for color attachments
    ///         when the renderpass ends
    /// @param finalLayoutDepth Image layout for depth attachment
    ///         when the renderpass ends
    /// @param startingOp Operation for color & depth buffers
    ///         when renderpass starts.
    /// @param name For debugging
    RenderPass(
        VulkanContext* ctx,
        VkFormat colorFormat,
        int numLayers,
        VkFormat depthFormat,
        VkImageLayout finalLayoutColor,
        VkImageLayout finalLayoutDepth,
        VkAttachmentLoadOp startingOp,
        std::string name
    );
    
  private:
    RenderPass(const RenderPass&) = delete;
    void operator=(const RenderPass&) = delete;
};
