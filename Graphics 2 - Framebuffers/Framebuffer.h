#pragma once
#include "vkhelpers.h"
#include "math2801.h"
#include "RenderPass.h"
#include <memory>
#include <functional>
#include <optional>

class Image;
class VertexManager;
class Primitive;
class DescriptorSetFactory;
class PushConstants;
class GraphicsPipeline;
class DescriptorSet;
class VertexManager;



/// A Framebuffer is a render target, either the window or else an offscreen image.
class Framebuffer {
public:

    /// Initialize the subsystem.
    /// @param ctx The context
    static void initialize(VulkanContext* ctx);

    /// Return true if subsystem was initialized
    /// @return True if initialized; false if not
    static bool initialized();

    /// Width of the framebuffer
    unsigned width;

    /// Height of the framebuffer
    unsigned height;

    /// Number of layers in the framebuffer
    unsigned numLayers;

    /// Format of the image associated with the framebuffer
    VkFormat format;

    /// Name, for debugging
    std::string name;

    /// RenderPass that discards previous framebuffer contents (Uses VK_LOAD_OP_DONT_CARE)
    RenderPass* allLayersRenderPassDiscard;

    /// RenderPass that retains initial data. Note: This must not be the initial RenderPass for
    /// a given frame if you are drawing to an onscreen window.
    RenderPass* allLayersRenderPassKeep;

    /// RenderPass that clears the screen before rendering.
    RenderPass* allLayersRenderPassClear;

    /// RenderPass for drawing to a single layer of the framebuffer while discarding previous contents (VK_LOAD_OP_DONT_CARE).
    RenderPass* singleLayerRenderPassDiscard;

    /// RenderPass for drawing to a single layer of the framebuffer while retaining previous contents.
    RenderPass* singleLayerRenderPassKeep;

    /// RenderPass for drawing to a single layer of the framebuffer while clearing previous contents.
    RenderPass* singleLayerRenderPassClear;

    /// Create a Framebuffer associated with the onscreen window.
    Framebuffer();

    /// Create offscreen Framebuffer
    /// @param w Width
    /// @param h Height
    /// @param layers Number of layers; must be positive
    /// @param VkFormat Format of image
    /// @param name For debugging
    Framebuffer(
        unsigned w, unsigned h, unsigned layers, VkFormat format, std::string name
    );

    /// Destructor to release resources.
    ~Framebuffer();


    /// Begin a renderpass that draws into all layers of this framebuffer.
    /// The initial contents of the framebuffer are undefined.
    /// @param cmd Command buffer
    void beginRenderPassDiscardContents(VkCommandBuffer cmd);

    /// Begin a renderpass that draws into all layers of this framebuffer.
    /// The initial contents of the framebuffer are retained as-is.
    /// @param cmd Command buffer
    void beginRenderPassKeepContents(VkCommandBuffer cmd);

    /// Begin a renderpass that draws into all layers of this framebuffer.
    /// The framebuffer is cleared before rendering starts.
    /// The depth buffer is cleared to 1.0 and the stencil buffer is cleared to 0.
    /// @param cmd Command buffer
    /// @param r,g,b,a The clear color
    void beginRenderPassClearContents(VkCommandBuffer cmd, float r, float g, float b, float a);

    /// Begin a renderpass that draws into one layer of this framebuffer.
    /// The initial contents of the framebuffer are undefined.
    /// @param layerIndex The layer to draw to
    /// @param cmd Command buffer
    void beginOneLayerRenderPassDiscardContents(int layerIndex, VkCommandBuffer cmd);

    /// Begin a renderpass that draws into one layer of this framebuffer.
    /// The initial contents of the framebuffer are retained as-is.
    /// @param layerIndex The layer to draw to
    /// @param cmd Command buffer
    void beginOneLayerRenderPassKeepContents(int layerIndex, VkCommandBuffer cmd);

    /// Begin a renderpass that draws into one layer of this framebuffer.
    /// The framebuffer is cleared before rendering starts. The depth buffer is cleared to 1.0 and the stencil buffer is cleared to 0.
    /// @param layerIndex The layer to draw to
    /// @param cmd Command buffer
    /// @param r,g,b,a The clear color
    void beginOneLayerRenderPassClearContents(int layerIndex, VkCommandBuffer cmd, float r, float g, float b, float a);

    /// End a render pass and build mipmaps.
    /// @param cmd The command buffer
    void endRenderPass(VkCommandBuffer cmd);

    /// End a render pass and do not build mipmaps.
    /// This should be used if you intend to start another
    /// renderpass with the same framebuffer without
    /// reading the framebuffer's contents
    /// @param cmd The command buffer
    void endRenderPassNoMipmaps(VkCommandBuffer cmd);

    /// Clear the color, depth, and/or stencil buffers associated with this Framebuffer
    /// @param cmd The command buffer
    /// @param clearColorValue If provided, the color to use for the clear; if absent, do not clear the color channels.
    /// @param clearDepthValue If provided, the depth value to use for the clear; if absent, do not clear depth buffer.
    /// @param clearStencilValue If provided, the stencil value to use for the clear; if absent, do not clear stencil buffer.
    void clear(VkCommandBuffer cmd,
        std::optional<VkClearColorValue> clearColorValue,
        std::optional<float> clearDepthValue,
        std::optional<std::uint32_t> clearStencilValue);

    /// Clear the color, depth, and stencil buffers associated with this Framebuffer.
    /// The depth buffer will be cleared to 1.0; the stencil buffer is cleared to zero.
    /// @param cmd The command buffer
    /// @param r,g,b,a The clear color
    void clear(VkCommandBuffer cmd, float r, float g, float b, float a);

    /// Blur this Framebuffer; this cannot be called on a
    /// Framebuffer associated with the window. (It must be
    /// an offscreen image). Note that this function
    /// changes the currently bound pipeline and descriptor sets,
    /// so you must rebind any pipeline or descriptor sets that you need.
    /// @param radius The blur radius. Must be <= 56
    /// @param layer The layer to blur
    /// @param scaleFactor Each pixel channel will be multiplied by this value after blurring
    /// @param cmd The command buffer
    /// @param currentVertexManager This function changes the currently bound vertex manager;
    ///        the parameter provided will be rebound as the vertex manager before blur() returns.
    ///        This parameter may be null.
    void blur(unsigned radius, unsigned layer, float scaleFactor,
        VkCommandBuffer cmd, VertexManager* currentVertexManager);

    /// Blur this Framebuffer; this cannot be called on a
    /// Framebuffer associated with the window. (It must be
    /// an offscreen image). Note that this function
    /// changes the currently bound pipeline and descriptor sets,
    /// so you must rebind any pipeline or descriptor sets that you need.
    /// @param radius The blur radius. Must be <= 56
    /// @param layer The layer to blur
    /// @param scaleFactor Each pixel channel will be multiplied by this value after blurring
    /// @param cmd The command buffer
    /// @param currentVertexManager This function changes the currently bound vertex manager;
    ///        the parameter provided will be rebound as the vertex manager before blur() returns.
    ///        This parameter may be null.
    /// @param doDistanceDependentBlur True to do a distance-dependent blur, suitable for
    ///        depth of field effects.
    void blur(unsigned radius, unsigned layer, float scaleFactor,
        VkCommandBuffer cmd, VertexManager* currentVertexManager,
        bool doDistanceDependentBlur);


    /// Return the most recently rendered image. This requires that at least one
    /// render pass has been completed on this Framebuffer (it will use whatever
    /// image was last rendered in a renderpass).
    Image* currentImage();

    /// Returns view of most recently rendered depth buffer.
    /// This requires that at least one
    /// render pass has been completed on this Framebuffer (it will use whatever
    /// image was last rendered in a renderpass).
    VkImageView currentDepthBufferView();

private:
    void beginOneLayerRenderPassDiscardContentsWithIndex(int imageIndex, int layerIndex, VkCommandBuffer cmd);
    void beginOneLayerRenderPassKeepContentsWithIndex(int imageIndex, int layerIndex, VkCommandBuffer cmd);
    void beginRenderPassHelper(int imageIndex, int layerIndex, VkCommandBuffer cmd,
        VkAttachmentLoadOp loadOp, float r, float g, float b, float a);
    std::vector<VkFramebuffer> allLayersFramebuffers;   //one per swapchain image
    std::vector< std::vector<VkFramebuffer> > singleLayerFramebuffers;  //outer=swapchain index, inner=layer index

    int completedRenderIndex = -1;            //frame that we last completed a rendering to: 0...num swapchain images-1
    int currentRenderIndex = -1;              // frame that we are currently rendering into; -1 if none

    bool insideRenderpass = false;            //true if we're in a renderpass
    std::vector<Image*> colorBuffers;       //one per swapchain image
    std::vector<Image*> depthBuffers;       //one per swapchain image
    std::vector<VkImageView> depthBufferViews;  // one per swapchain image; view only includes depth aspect so we can use for fbo's

    bool isDefaultFB;
    bool pushedToGPU = false;
    GraphicsPipeline* blurPipeline = nullptr;
    GraphicsPipeline* blurDDPipelineWriteToHelper = nullptr;
    GraphicsPipeline* blurDDPipelineWriteToFB = nullptr;
    void pushToGPU();

    Framebuffer(
        bool blurrable, unsigned w, unsigned h, unsigned layers, VkFormat format, std::string name
    );

    Framebuffer* blurHelper = nullptr;    //pointer into map, not a private FB
    DescriptorSet* blurDescriptorSet;
    Framebuffer(const Framebuffer&) = delete;
    void operator=(const Framebuffer&) = delete;
};
