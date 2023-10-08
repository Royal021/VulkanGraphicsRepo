#include "Pipeline.h"
#include "PushConstants.h"
#include "mischelpers.h"
#include "VertexManager.h"
#include "Descriptors.h"
#include "CleanupManager.h"
#include "Framebuffer.h"
#include "RenderPass.h"
#include "utils.h"
#include <cstring>
#include <assert.h>
#include <optional>
#include <array>


static bool initialized=false;
static Pipeline* current_;


static void frameBeginCallback(int /*imageIndex*/, VkCommandBuffer )
{
    current_ = nullptr;
}

static void frameEndCallback(int /*imageIndex*/, VkCommandBuffer )
{
    current_ = nullptr;
}

static void initialize(VulkanContext*){
    if(!initialized){
        utils::registerFrameBeginCallback( frameBeginCallback );
        utils::registerFrameEndCallback( frameEndCallback );
        initialized=true;
    }
}

PipelineLayout::PipelineLayout(
    VulkanContext* ctx,
    PushConstants* pushConstants_,
    std::array<DescriptorSetLayout*,3> descriptorSetLayouts_,
    std::string name_
){

    this->name=name_;
    this->descriptorSetLayouts=descriptorSetLayouts_;
    this->pushConstants = pushConstants_;

    VkPushConstantRange pushConstantRange{
        .stageFlags=VK_SHADER_STAGE_ALL,
        .offset=0,
        .size=(unsigned)pushConstants->byteSize
    };

    std::vector<VkDescriptorSetLayout> tmp;
    for(DescriptorSetLayout* d : descriptorSetLayouts ){
        if(d){
            tmp.push_back(d->layout);
        }
    }

    check(vkCreatePipelineLayout(
        ctx->dev,
        VkPipelineLayoutCreateInfo{
            .sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            .pNext=nullptr,
            .flags=0,
            .setLayoutCount=(unsigned)tmp.size(),
            .pSetLayouts=tmp.data(),
            .pushConstantRangeCount=unsigned( pushConstants->byteSize ? 1 : 0),
            .pPushConstantRanges=&pushConstantRange
        },
        nullptr,
        &(this->pipelineLayout)
    ));

    ctx->setObjectName(this->pipelineLayout,"pipeline layout "+name);

    CleanupManager::registerCleanupFunction( [this,ctx](){
        vkDestroyPipelineLayout(
            ctx->dev,
            this->pipelineLayout,
            nullptr
        );
    });

}


Pipeline::Pipeline(VulkanContext* ctx_, PipelineLayout* pipelineLayout_,
        VkPipelineBindPoint bindPoint_, std::string name_)
{
    initialize(ctx);
    this->ctx=ctx_;
    this->pipelineLayout=pipelineLayout_;
    this->bindPoint=bindPoint_;
    this->name=name_;
}

void Pipeline::use(VkCommandBuffer cmd)
{
    if(this->pipeline == VK_NULL_HANDLE )
        this->finishInit();
    vkCmdBindPipeline(cmd,this->bindPoint,this->pipeline);
    current_ = this;
}


//FIXME: This assumes we only build one command list at a time
Pipeline* Pipeline::current(){
    if(!current_)
        throw std::runtime_error("There is no active pipeline");
    return current_;
}




