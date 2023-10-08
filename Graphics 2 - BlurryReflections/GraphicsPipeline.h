#pragma once
#include "vkhelpers.h"
#include "VertexInput.h"
#include <variant>
#include <list>
#include <optional>
#include "Pipeline.h"

class DescriptorSetFactory;
class DescriptorSet;
class DescriptorSetLayout;
class PushConstants;
class RenderPass;
class Framebuffer;

/// A pipeline for rendering graphics data.  
class GraphicsPipeline : public Pipeline{
  public:

    /// The renderpass for the pipeline. Note that any compatible renderpass
    /// may be used with this pipeline. Section 8.2 of the Vulkan specification
    /// defines renderpass compatibility. Two renderpasses are compatible if:
    /// - Their color attachments are compatible
    ///     - The attachment formats are same
    ///     - The sample counts are same
    ///     - As a special case: VK_ATTACHMENT_UNUSED is always compatible with anything
    /// - Their input attachments are compatible (Note: we don't use these)
    /// - Their Resolve attachments are compatible (This only applies to multisampling)
    /// - Their Depth/stencil attachments are compatible
    /// - All other characteristics of the renderpasses must be identical except:
    ///     - Initial & final layouts may differ
    ///     - Load & store op's may differ
    ///     - Image layout in attachments may differ
    RenderPass* renderPass;
    
    /// Create a GraphicsPipeline
    /// @param ctx The associated context
    /// @param pipelineLayout The layout for the pipeline
    /// @param pipelineVertexInputStateCreateInfo Vertex puller input parameters
    /// @param framebuffer The associated framebuffer; note that we only use the width & height.
    ///                    The framebuffer's renderpass is used to get an initial renderpass
    ///                    but any compatible renderpass can be used with this pipeline.
    /// @param name For debugging
    GraphicsPipeline(
        VulkanContext* ctx,
        PipelineLayout* pipelineLayout,
        VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo,
        Framebuffer* framebuffer, 
        std::string name
    );
    
    /// Clone a GraphicsPipeline from another existing one.
    /// The new pipeline will be initialized to have the same state (options)
    /// as the existing one; it can then be modified with set().
    GraphicsPipeline( GraphicsPipeline* parent,  std::string name );
    
    /// Return a cloned copy of this pipeline. See 
    /// The new pipeline will be initialized to have the same state (options)
    /// as the existing one; it can then be modified with set().
    GraphicsPipeline* clone(std::string name);
    
    /// Set the state for the pipeline. This cannot be called after use() has been called.
    /// @param op The option to set
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(VkPipelineVertexInputStateCreateInfo op);

    /// Set the state for the pipeline. This cannot be called after use() has been called.
    /// @param op The option to set
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(VkPipelineInputAssemblyStateCreateInfo op);

    /// Set the state for the pipeline. This cannot be called after use() has been called.
    /// @param op The option to set
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(VkPipelineTessellationStateCreateInfo op);

    /// Set the state for the pipeline. This cannot be called after use() has been called.
    /// @param op The option to set
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(VkPipelineViewportStateCreateInfo op);

    /// Set the state for the pipeline. This cannot be called after use() has been called.
    /// @param op The option to set
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(VkPipelineRasterizationStateCreateInfo op);

    /// Set the state for the pipeline. This cannot be called after use() has been called.
    /// @param op The option to set
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(VkPipelineMultisampleStateCreateInfo op);

    /// Set the state for the pipeline. This cannot be called after use() has been called.
    /// @param op The option to set
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(VkPipelineDepthStencilStateCreateInfo op);

    /// Set the state for the pipeline. This cannot be called after use() has been called.
    /// @param op The option to set
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(VkPipelineColorBlendStateCreateInfo op);

    /// Set the state for the pipeline. This cannot be called after use() has been called.
    /// @param op The option to set
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(VkPipelineColorBlendAttachmentState op);

    /// Set the state for the pipeline. This cannot be called after use() has been called.
    /// @param op The option to set
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(VkPipelineShaderStageCreateInfo op);

    /// Set the state for the pipeline. This cannot be called after use() has been called.
    /// @param op The framebuffer to use (only width & height are relevant)
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(Framebuffer* op);    

    /// Set the state for the pipeline. This cannot be called after use() has been called.
    /// @param op The renderpass to use
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(RenderPass* op);

    /// Set the blend state for all attachments to the framebuffer.
    /// This cannot be called after use() has been called.
    /// @param srcFactor The source color & alpha factor (ex: VK_BLEND_FACTOR_SRC_ALPHA)
    /// @param dstFactor The destination color & alpha factor (ex: VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA)
    /// @return A pointer to this GraphicsPipeline, to facilitate call chaining.
    GraphicsPipeline* set(VkBlendFactor srcFactor, VkBlendFactor dstFactor); 
    
    /// Set the depth/stencil state for the pipeline
    /// This cannot be called after use() has been called.
    /// Both front and back stencil parameters are set to the indicated values
    /// @param depthTestEnable True to enable the depth test; false to disable it
    /// @param depthWriteEnable True to enable writing to the depth test; false to disable it
    /// @param stencilEnable True to enable the stencil test; false to disable it
    /// @param stencilOp The stencil test operation (ex: VK_COMPARE_OP_EQUAL)
    /// @param ref The stencil reference value
    /// @param stencilFail Action to take when the stencil test fails
    /// @param depthFail Action to take when the stencil test passes but the depth test fails.
    /// @param pass Action to take when the stencil and depth tests pass.
    
    GraphicsPipeline* set(bool depthTestEnable, bool depthWriteEnable, bool stencilEnable, 
                         VkCompareOp stencilOp, std::uint32_t ref, 
                         VkStencilOp stencilFail,VkStencilOp depthFail, VkStencilOp pass);
    
  private:
  
    void setDefaults();
    void finishInit() override;

    bool isChildPipeline;
    
    //these go together. Must use std::list so strings don't
    //move in memory
    std::vector<VkPipelineShaderStageCreateInfo> pipelineShaderStageCreateInfo;
    std::list<std::string> shaderEntryPoints;
    
    //these go together
    std::vector<VkViewport> viewports;
    std::vector<VkRect2D> scissors;
    VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo;

    //these go together
    VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo;
    std::vector<VkSampleMask> sampleMasks;

    //these go together
    VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo;
    std::vector<VkPipelineColorBlendAttachmentState> blendAttachmentState;

    //no pointers in here
    VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo;

    //no pointers in here
    VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo;
    
    //no pointers in here
    VkPipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo;
    
    //no pointers in here
    std::optional<VkPipelineTessellationStateCreateInfo> pipelineTessellationStateCreateInfo;
    
    //these go together
    VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo;
    std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
    
    //obtained from Framebuffer
    float width,height;
    
    //renderpass to use if the user didn't give us a renderpass.
    //See comment in the Pipeline cloning constructor for
    //an explanation.
    RenderPass* lastResortRenderpass;
    
    ///////
    
    //flag error if use() has been called before set()
    void checkSettable();
    
};


