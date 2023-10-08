#include "vkhelpers.h"
#include "ComputePipeline.h"
#include "PushConstants.h"
#include "mischelpers.h"
#include "Descriptors.h"
#include "CleanupManager.h"
#include <cstring>
#include <assert.h>
   
ComputePipeline::ComputePipeline(
    VulkanContext* ctx_,
    PipelineLayout* pipelineLayout_,
    VkPipelineShaderStageCreateInfo computeShader_,
    std::string name_ ) : Pipeline(ctx_,pipelineLayout_,VK_PIPELINE_BIND_POINT_COMPUTE,name_)
{
    this->computeShader=computeShader_;
}

void ComputePipeline::finishInit()
{
    
    assert(this->pipeline == VK_NULL_HANDLE);
    
    VkComputePipelineCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .stage = this->computeShader,
        .layout = this->pipelineLayout->pipelineLayout,
        .basePipelineHandle = VK_NULL_HANDLE,
        .basePipelineIndex = 0
    };
        
    check(vkCreateComputePipelines( this->ctx->dev,
        nullptr,    //cache
        1,          //count
        &info,
        nullptr,    //allocators
        &this->pipeline
    ));
    

    ctx->setObjectName(this->pipeline, this->name);
    
    CleanupManager::registerCleanupFunction( [this](){
        vkDestroyPipeline(this->ctx->dev,this->pipeline,nullptr);
    });
    
}


