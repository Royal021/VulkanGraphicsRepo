#pragma once
#include "vkhelpers.h"
#include <array>

class DescriptorSetLayout;
class PushConstants;

/// Describes layout of a pipeline
class PipelineLayout{
  public:

    /// Constructor
    /// @param ctx The associated context
    /// @param pushConstants Push constants that will be used with this pipeline
    /// @param descriptorSetLayouts Layout of the first three descriptor sets
    ///         that will be used with the pipeline. If a set will not
    ///         be used, null may be passed in for that item.
    /// @param name Name, for debuggin
    PipelineLayout( VulkanContext* ctx,
                    PushConstants* pushConstants,
                    std::array<DescriptorSetLayout*,3> descriptorSetLayouts,
                    std::string name);

    /// The descriptor sets used for this layout
    std::array<DescriptorSetLayout*,3> descriptorSetLayouts;

    /// The push constants used for the pipeline
    PushConstants* pushConstants;

    /// The pipline layout itself
    VkPipelineLayout pipelineLayout;

    /// Name, for debugging
    std::string name;
};


/// Base class for all pipeline objects (see GraphicsPipeline
/// and ComputePipeline). This is an abstract class
/// and is not instantiated directly.
class Pipeline{
  public:

    /// Layout of the pipeline
    PipelineLayout* pipelineLayout;

    /// Name, for debugging
    std::string name;

    /// Constructor
    /// @param ctx Associated context
    /// @param pipelineLayout The pipeline's layout
    /// @param bindPoint Type of pipeline: VK_PIPELINE_BIND_POINT_GRAPHICS
    ///     or VK_PIPELINE_BIND_POINT_COMPUTE
    /// @param name For debugging
    Pipeline(VulkanContext* ctx, PipelineLayout* pipelineLayout,
        VkPipelineBindPoint bindPoint, std::string name);

    /// Activate this pipeline.
    /// @param cmd The command buffer
    void use(VkCommandBuffer cmd);

    /// Returns the most recently used pipeline (see use()).
    /// If no pipeline has been used for the current frame,
    /// an exception is thrown.
    /// @return The pipeline
    static Pipeline* current();

  protected:

    virtual void finishInit()=0;

    VulkanContext* ctx;
    VkPipeline pipeline = VK_NULL_HANDLE;
    VkPipelineBindPoint bindPoint;

    Pipeline(const Pipeline&) = delete;
    void operator=(const Pipeline&) = delete;

};


