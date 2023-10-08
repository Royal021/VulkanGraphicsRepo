#pragma once
#include "vkhelpers.h"
#include "Pipeline.h"
#include "VertexInput.h"

class DescriptorSetFactory;
class DescriptorSet;
class DescriptorSetLayout;
class PushConstants;
class PipelineLayout;
  
/// A pipeline to be used for compute shader execution.
class ComputePipeline : public Pipeline{
  public:

    /// Create the pipeline.
    /// @param ctx The owning context
    /// @param pipelineLayout the pipeline layout
    /// @param computeShader The compute shader
    /// @param name For debugging purposes.
    ComputePipeline(
        VulkanContext* ctx,
        PipelineLayout* pipelineLayout,
        VkPipelineShaderStageCreateInfo computeShader,
        std::string name
    );
    
  private:
  
    VkPipelineShaderStageCreateInfo computeShader;
    void finishInit() override;

};


