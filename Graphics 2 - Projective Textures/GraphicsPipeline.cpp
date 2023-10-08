#include "GraphicsPipeline.h"
#include "PushConstants.h"
#include "mischelpers.h"
#include "VertexManager.h"
#include "Descriptors.h"
#include "CleanupManager.h"
#include "Framebuffer.h"
#include "RenderPass.h"
#include <cstring>
#include <assert.h>
#include <optional>

 

GraphicsPipeline* GraphicsPipeline::clone(std::string name_)
{
    return new GraphicsPipeline(this,name_);
}


GraphicsPipeline::GraphicsPipeline( 
    GraphicsPipeline* parent, 
    std::string name_) : Pipeline(parent->ctx,parent->pipelineLayout,VK_PIPELINE_BIND_POINT_GRAPHICS,name_)
{
    //FIXME: Verify everything is being copied
    this->isChildPipeline = true;
    this->width=parent->width;
    this->height=parent->height;
    
    //don't set the renderpass yet
    //Rationale: If we clone a defaultFB pipeline for use with
    //an offscreen FB, the renderpasses will be different (because
    //the initial formats of the two pipelines will be different).
    //So we leave this as null until the last minute, when
    //we use the FB's default renderpass if the user hasn't explicitly
    //set a renderpass.
    this->renderPass=nullptr;
    this->lastResortRenderpass=parent->renderPass;
    if(!this->lastResortRenderpass)
        this->lastResortRenderpass=parent->lastResortRenderpass;
        
    for(auto& p : parent->pipelineShaderStageCreateInfo)
        this->set(p);
    this->set(parent->pipelineViewportStateCreateInfo       );
    this->set(parent->pipelineMultisampleStateCreateInfo    );
    this->set(parent->pipelineColorBlendStateCreateInfo     );
    this->set(parent->pipelineInputAssemblyStateCreateInfo  );
    this->set(parent->pipelineRasterizationStateCreateInfo  );
    this->set(parent->pipelineDepthStencilStateCreateInfo   );
    if( parent->pipelineTessellationStateCreateInfo.has_value() )
        this->set(parent->pipelineTessellationStateCreateInfo.value()   );
    this->set(parent->pipelineVertexInputStateCreateInfo    );
}

GraphicsPipeline::GraphicsPipeline(
    VulkanContext* ctx_,
    PipelineLayout* pipelineLayout_,
    VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo_,
    Framebuffer* framebuffer, 
    std::string name_) : Pipeline(ctx_,pipelineLayout_,VK_PIPELINE_BIND_POINT_GRAPHICS,name_)
{
    this->isChildPipeline=false;
    this->width=(float)framebuffer->width;
    this->height=(float)framebuffer->height;
    this->renderPass=framebuffer->allLayersRenderPassDiscard;
    this->setDefaults();
    this->set(pipelineVertexInputStateCreateInfo_);
}

void GraphicsPipeline::setDefaults()
{
    this->set(VkPipelineInputAssemblyStateCreateInfo{
            .sType=VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
            .pNext=nullptr,
            .flags=0,
            .topology=VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
            .primitiveRestartEnable=VK_FALSE
        }
    );

    {
        VkViewport vport{
            .x=0,
            .y=0,
            .width = this->width,
            .height = this->height,
            .minDepth=0,
            .maxDepth = 1.0f
        };
        VkRect2D scissor{
            .offset=VkOffset2D{
                .x=0,
                .y=0
            },
            .extent = VkExtent2D{
                .width = (unsigned)(this->width),
                .height = (unsigned)(this->height),
            }
        };
        this->set(VkPipelineViewportStateCreateInfo{
            .sType=VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
            .pNext=nullptr,
            .flags=0,
            .viewportCount = 1,
            .pViewports = &vport,
            .scissorCount = 1,
            .pScissors = &scissor
        });
    }
    

    this->set(VkPipelineRasterizationStateCreateInfo{
        .sType=VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .pNext=nullptr,
        .flags=0,
        .depthClampEnable=0,
        .rasterizerDiscardEnable=0,
        .polygonMode=VK_POLYGON_MODE_FILL,
        .cullMode=0,
        .frontFace=VK_FRONT_FACE_COUNTER_CLOCKWISE,
        .depthBiasEnable=0,
        .depthBiasConstantFactor=0,
        .depthBiasClamp=0,
        .depthBiasSlopeFactor=0,
        .lineWidth = 1.0f
    });

    this->set(VkPipelineMultisampleStateCreateInfo{
        .sType=VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .pNext=nullptr,
        .flags=0,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
        .sampleShadingEnable=0,
        .minSampleShading = 1.0f,
        .pSampleMask=nullptr,
        .alphaToCoverageEnable=0,
        .alphaToOneEnable=0,
    });

    this->set(VkPipelineDepthStencilStateCreateInfo{
        .sType=VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .pNext=nullptr,
        .flags=0,
        .depthTestEnable=VK_TRUE,
        .depthWriteEnable=VK_TRUE,
        .depthCompareOp=VK_COMPARE_OP_LESS_OR_EQUAL,
        .depthBoundsTestEnable=VK_FALSE,
        .stencilTestEnable=VK_FALSE,
        .front=VkStencilOpState{
            .failOp=VK_STENCIL_OP_KEEP,
            .passOp=VK_STENCIL_OP_KEEP,
            .depthFailOp=VK_STENCIL_OP_KEEP,
            .compareOp=VK_COMPARE_OP_ALWAYS,
            .compareMask=0xff,
            .writeMask=0xff,
            .reference=0
        },
        .back=VkStencilOpState{
            .failOp=VK_STENCIL_OP_KEEP,
            .passOp=VK_STENCIL_OP_KEEP,
            .depthFailOp=VK_STENCIL_OP_KEEP,
            .compareOp=VK_COMPARE_OP_ALWAYS,
            .compareMask=0xff,
            .writeMask=0xff,
            .reference=0
        },
        .minDepthBounds=0.0,
        .maxDepthBounds=1.0
    });

    {
        VkPipelineColorBlendAttachmentState att{
            .blendEnable=VK_TRUE,
            .srcColorBlendFactor=VK_BLEND_FACTOR_ONE,
            .dstColorBlendFactor=VK_BLEND_FACTOR_ZERO,
            .colorBlendOp=VK_BLEND_OP_ADD,
            .srcAlphaBlendFactor=VK_BLEND_FACTOR_ONE,
            .dstAlphaBlendFactor=VK_BLEND_FACTOR_ZERO,
            .alphaBlendOp=VK_BLEND_OP_ADD,
            .colorWriteMask = (
                VK_COLOR_COMPONENT_R_BIT |
                VK_COLOR_COMPONENT_G_BIT |
                VK_COLOR_COMPONENT_B_BIT |
                VK_COLOR_COMPONENT_A_BIT
            )
        };
        this->set(VkPipelineColorBlendStateCreateInfo{
            .sType=VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
            .pNext=nullptr,
            .flags=0,
            .logicOpEnable=0,
            .logicOp=VK_LOGIC_OP_COPY,
            .attachmentCount=1,
            .pAttachments = &att,
            .blendConstants={0,0,0,0}
        });
    }
    
    this->pipelineTessellationStateCreateInfo=std::optional<VkPipelineTessellationStateCreateInfo>();
    
}
    
GraphicsPipeline* GraphicsPipeline::set(VkPipelineVertexInputStateCreateInfo opt)
{
    this->pipelineVertexInputStateCreateInfo = opt;
    
    this->vertexBindingDescriptions.resize(opt.vertexBindingDescriptionCount);
    std::memcpy(this->vertexBindingDescriptions.data(), 
                opt.pVertexBindingDescriptions, 
                sizeof(this->vertexBindingDescriptions[0]) * this->vertexBindingDescriptions.size()
    );
    this->pipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = this->vertexBindingDescriptions.data();
    
    this->attributeDescriptions.resize(opt.vertexAttributeDescriptionCount);
    std::memcpy( this->attributeDescriptions.data(),
                 opt.pVertexAttributeDescriptions,
                 sizeof(this->attributeDescriptions[0]) * this->attributeDescriptions.size()
    );
    this->pipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = this->attributeDescriptions.data();
    return this;
}

    
    
GraphicsPipeline* GraphicsPipeline::set( VkPipelineInputAssemblyStateCreateInfo opt)
{
    checkSettable();
    this->pipelineInputAssemblyStateCreateInfo = opt;
    return this;
}

GraphicsPipeline* GraphicsPipeline::set( VkPipelineViewportStateCreateInfo opt)
{
    checkSettable();
    this->pipelineViewportStateCreateInfo = opt;
    
    //make private copy that won't have external pointer dependencies
    this->viewports.resize( pipelineViewportStateCreateInfo.viewportCount );
    std::memcpy( this->viewports.data(), pipelineViewportStateCreateInfo.pViewports, sizeof(this->viewports[0])*this->viewports.size() );
    this->pipelineViewportStateCreateInfo.pViewports = this->viewports.data();
            
    this->scissors.resize( pipelineViewportStateCreateInfo.scissorCount );
    std::memcpy( this->scissors.data(), pipelineViewportStateCreateInfo.pScissors, sizeof(this->scissors[0])*this->scissors.size() );
    this->pipelineViewportStateCreateInfo.pScissors = this->scissors.data();
    
    return this;
}

GraphicsPipeline* GraphicsPipeline::set( VkPipelineRasterizationStateCreateInfo opt)
{
    checkSettable();
    this->pipelineRasterizationStateCreateInfo = opt;
    return this;
}

GraphicsPipeline* GraphicsPipeline::set( VkPipelineMultisampleStateCreateInfo opt)
{
    checkSettable();
    this->pipelineMultisampleStateCreateInfo = opt;
    if( opt.pSampleMask ){
        int numMasks = opt.rasterizationSamples/32;
        if( opt.rasterizationSamples % 32 )
            ++numMasks;
        this->sampleMasks.resize(numMasks);
        std::memcpy(this->sampleMasks.data(), opt.pSampleMask, sizeof(this->sampleMasks[0])*this->sampleMasks.size());
        this->pipelineMultisampleStateCreateInfo.pSampleMask = this->sampleMasks.data();
    }
    return this;
}

GraphicsPipeline* GraphicsPipeline::set( VkPipelineDepthStencilStateCreateInfo opt)
{
    checkSettable();
    this->pipelineDepthStencilStateCreateInfo = opt;
    return this;
}

GraphicsPipeline* GraphicsPipeline::set( VkPipelineColorBlendStateCreateInfo opt)
{
    checkSettable();
    this->pipelineColorBlendStateCreateInfo = opt;
    this->blendAttachmentState.resize( opt.attachmentCount );
    for(unsigned i=0;i<opt.attachmentCount;++i){
        this->blendAttachmentState[i] = opt.pAttachments[i];
    }
    this->pipelineColorBlendStateCreateInfo.pAttachments = this->blendAttachmentState.data();
    //we might rewrite pAttachments when we setup the pipeline if
    //the final framebuffer has a different number of render targets
    return this;
}

GraphicsPipeline* GraphicsPipeline::set( VkPipelineTessellationStateCreateInfo opt)
{
    checkSettable();
    this->pipelineTessellationStateCreateInfo = std::optional<VkPipelineTessellationStateCreateInfo>(opt);
    return this;
}

GraphicsPipeline* GraphicsPipeline::set( VkPipelineColorBlendAttachmentState opt)
{
    //we might rewrite pAttachments when we setup the pipeline if
    //the final framebuffer has a different number of render targets
    checkSettable();

    this->blendAttachmentState.resize(1);
    this->blendAttachmentState[0] = opt;
    this->pipelineColorBlendStateCreateInfo.pAttachments = this->blendAttachmentState.data();
    return this;
}

//~ GraphicsPipeline* GraphicsPipeline::set( std::vector<VkPipelineShaderStageCreateInfo> optv)
//~ {
    //~ for(const VkPipelineShaderStageCreateInfo& opt : optv ){
        //~ this->set(opt);
    //~ }
//~ }

GraphicsPipeline* GraphicsPipeline::set( VkPipelineShaderStageCreateInfo opt)
{
    //see if we already have a shader of the given type
    //If so, remove it
    checkSettable();
    
    auto it1 = this->pipelineShaderStageCreateInfo.begin();
    auto it2 = this->shaderEntryPoints.begin();
    while( it1 != this->pipelineShaderStageCreateInfo.end() ){
        if( it1->stage == opt.stage ){
            it1 = this->pipelineShaderStageCreateInfo.erase(it1);
            it2 = this->shaderEntryPoints.erase(it2);
        } else {
            it1++;
            it2++;
        }
    }
            
    this->shaderEntryPoints.push_back( std::string( opt.pName ) );
    this->pipelineShaderStageCreateInfo.push_back(VkPipelineShaderStageCreateInfo{
        .sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .pNext=nullptr,
        .flags=0,
        .stage=opt.stage,
        .module=opt.module,       
        .pName=this->shaderEntryPoints.back().c_str(),
        .pSpecializationInfo=nullptr
    });
    return this;
}

GraphicsPipeline* GraphicsPipeline::set(Framebuffer* fb)
{
    checkSettable();
    this->width=(float)fb->width;
    this->height=(float)fb->height;
    for(auto& v : this->viewports ){
        v.width = (float) fb->width;
        v.height = (float) fb->height;
    }
    for(auto& s : this->scissors ){
        s.extent.width = (unsigned)fb->width;
        s.extent.height = (unsigned)fb->height;
    }
    this->lastResortRenderpass = fb->allLayersRenderPassDiscard;
    //might adjust blend state later on so pAttachments is correct
    return this;
}

GraphicsPipeline* GraphicsPipeline::set(RenderPass* rp)
{
    checkSettable();
    this->renderPass = const_cast<RenderPass*>(rp);
    return this;
}

//~ GraphicsPipeline* GraphicsPipeline::set(VkStencilOpState opt)
//~ {
    //~ checkSettable();
    //~ this->pipelineDepthStencilStateCreateInfo.stencilTestEnable=VK_TRUE;
    //~ this->pipelineDepthStencilStateCreateInfo.front = opt;
    //~ this->pipelineDepthStencilStateCreateInfo.back = opt;
    //~ return this;
//~ }

GraphicsPipeline* GraphicsPipeline::set( VkBlendFactor srcFactor, VkBlendFactor dstFactor ) //BlendFactors op)
{
    //~ VkBlendFactor srcFactor = op.srcFactor;
    //~ VkBlendFactor dstFactor = op.dstFactor;
    this->set(
        VkPipelineColorBlendAttachmentState{
            .blendEnable=VK_TRUE,
            .srcColorBlendFactor=srcFactor,
            .dstColorBlendFactor=dstFactor,
            .colorBlendOp=VK_BLEND_OP_ADD,
            .srcAlphaBlendFactor=srcFactor,
            .dstAlphaBlendFactor=dstFactor,
            .alphaBlendOp=VK_BLEND_OP_ADD,
            .colorWriteMask = (
                VK_COLOR_COMPONENT_R_BIT |
                VK_COLOR_COMPONENT_G_BIT |
                VK_COLOR_COMPONENT_B_BIT |
                VK_COLOR_COMPONENT_A_BIT
            )
        }
    );
    return this;
}

GraphicsPipeline* GraphicsPipeline::set(bool depthTestEnable, bool depthWriteEnable, bool stencilEnable, VkCompareOp compareOp, std::uint32_t ref, VkStencilOp stencilFailOp, VkStencilOp depthFailOp, VkStencilOp passOp)
{
    //~ auto compareOp = std::get<0>(op);
    //~ auto ref = std::get<1>(op);
    //~ auto stencilFailOp = std::get<2>(op);
    //~ auto depthFailOp = std::get<3>(op);
    //~ auto passOp = std::get<4>(op);
    
    this->pipelineDepthStencilStateCreateInfo.depthTestEnable = (depthTestEnable ? VK_TRUE : VK_FALSE);
    this->pipelineDepthStencilStateCreateInfo.depthWriteEnable = (depthWriteEnable ? VK_TRUE : VK_FALSE);
    this->pipelineDepthStencilStateCreateInfo.stencilTestEnable= (stencilEnable ? VK_TRUE : VK_FALSE);
    this->pipelineDepthStencilStateCreateInfo.front = VkStencilOpState{
            .failOp=stencilFailOp,
            .passOp=passOp,
            .depthFailOp=depthFailOp,
            .compareOp=compareOp,
            .compareMask=0xff,
            .writeMask=0xff,
            .reference=ref
    };
    this->pipelineDepthStencilStateCreateInfo.back = this->pipelineDepthStencilStateCreateInfo.front;
    return this;
}

void GraphicsPipeline::checkSettable()
{
    if( this->pipeline != VK_NULL_HANDLE ){
        throw std::runtime_error("Cannot set options on pipeline after use() has been called");
    }
}

void GraphicsPipeline::finishInit()
{
    
    assert(this->pipeline == VK_NULL_HANDLE);
    assert(this->blendAttachmentState.size() > 0 );
 
    if( this->renderPass == nullptr ){
        //most likely this pipeline was cloned from an existing pipeline
        //and the user didn't give us an explicit renderpass.
        //Use one of the FB's default renderpasses.
        this->renderPass = this->lastResortRenderpass;
    }
    
    //last check for blend state. Use renderpass for number of layers
    //because we might be rendering to only one of the FB's layers
    if( (int)this->blendAttachmentState.size() != this->renderPass->numLayers &&
             this->blendAttachmentState.size() == 1 ){
                 
            //convenience: Replicate as many times as needed
            this->blendAttachmentState = std::vector<VkPipelineColorBlendAttachmentState>(
                this->renderPass->numLayers,
                this->blendAttachmentState[0]
            );
    }
    
    if( (int)this->blendAttachmentState.size() != this->renderPass->numLayers ){
        throw std::runtime_error("Renderpass uses " + 
            std::to_string(this->renderPass->numLayers) + " layers of target, " +
            "but blend state only specifies values for " + 
            std::to_string(this->blendAttachmentState.size())+ " layers");
    }
    
    this->pipelineColorBlendStateCreateInfo.pAttachments = this->blendAttachmentState.data();
    this->pipelineColorBlendStateCreateInfo.attachmentCount = (unsigned)this->blendAttachmentState.size();
    
    VkGraphicsPipelineCreateInfo pipeInfo{
        .sType=VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext=nullptr,
        .flags=0,
        .stageCount=(unsigned)pipelineShaderStageCreateInfo.size(),
        .pStages = this->pipelineShaderStageCreateInfo.data(),
        .pVertexInputState = &this->pipelineVertexInputStateCreateInfo,
        .pInputAssemblyState = &this->pipelineInputAssemblyStateCreateInfo,
        .pTessellationState=(this->pipelineTessellationStateCreateInfo.has_value() ? &(this->pipelineTessellationStateCreateInfo.value()) : nullptr),
        .pViewportState = &this->pipelineViewportStateCreateInfo,
        .pRasterizationState = &this->pipelineRasterizationStateCreateInfo,
        .pMultisampleState = &this->pipelineMultisampleStateCreateInfo,
        .pDepthStencilState = &this->pipelineDepthStencilStateCreateInfo,
        .pColorBlendState = &this->pipelineColorBlendStateCreateInfo,
        .pDynamicState = nullptr,
        .layout = this->pipelineLayout->pipelineLayout,
        //any compatible renderpass may be used with this pipeline
        //compatible means:
        //  1. Color attachments are compatible
        //      a. Formats are same
        //      b. Sample counts are same
        //      c. Special case: VK_ATTACHMENT_UNUSED = always compatible
        //  2. Input attachments are compatible (we don't use these)
        //  3. Resolve attachments are compatible (we don't use these)
        //  4. Depth/stencil attachments are compatible (we always use the same DS format)
        //  5. All other characteristics of renderpass must be identical except:
        //      a. Initial & final layouts may differ
        //      b. Load & store op's may differ
        //      c. Image layout in attachments may differ
        .renderPass = this->renderPass->renderPass,
        .subpass = 0,
        .basePipelineHandle=0,
        .basePipelineIndex=0
    };

    check(vkCreateGraphicsPipelines(
        ctx->dev,
        VK_NULL_HANDLE,
        1,
        &pipeInfo,
        nullptr,
        &(this->pipeline)
    ));

    ctx->setObjectName(this->pipeline, this->name);
    
    CleanupManager::registerCleanupFunction( [this](){
        vkDestroyPipeline(this->ctx->dev,this->pipeline,nullptr);
    });
    
}

 


