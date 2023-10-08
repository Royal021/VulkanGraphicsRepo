#include "RenderPass.h"
#include "CleanupManager.h"
#include <cassert>
#include <stdexcept>


static VkRenderPass make(
    VulkanContext* ctx,
    VkFormat colorFormat,
    int numLayers,
    VkFormat depthFormat,
    VkImageLayout initialLayoutColor,
    VkImageLayout initialLayoutDepth,
    VkImageLayout finalLayoutColor,
    VkImageLayout finalLayoutDepth,
    VkAttachmentLoadOp lop,
    std::string name)
{
    std::vector<VkAttachmentReference> colorAttachments(numLayers);
    for(int i=0;i<numLayers;++i){
        colorAttachments[i] = VkAttachmentReference{
            .attachment=(unsigned)i,
            //layout during the render
            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        };
    }
    
    VkAttachmentReference depthStencilAttachment{
        .attachment=(unsigned)numLayers,
        //layout during the render
        .layout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
    };

    VkSubpassDescription subpassDescription{
        .flags=0,
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .inputAttachmentCount=0,
        .pInputAttachments=nullptr,
        .colorAttachmentCount = (unsigned)colorAttachments.size(),
        .pColorAttachments = colorAttachments.data(),
        .pResolveAttachments=nullptr,
        .pDepthStencilAttachment=&depthStencilAttachment,
        .preserveAttachmentCount=0,
        .pPreserveAttachments=nullptr
    };

    VkSubpassDependency subpassDependency{
        .srcSubpass = VK_SUBPASS_EXTERNAL,
        .dstSubpass=0,
        .srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, //VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, //VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
        .srcAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT, 
        .dstAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT,
        .dependencyFlags=0
    };
    
    //+1 for depth buffer
    std::vector<VkAttachmentDescription> attachmentDescriptions(numLayers+1);
   
    //~ VkAttachmentLoadOp lop;
    //~ if( clearOnUse )
        //~ lop = VK_ATTACHMENT_LOAD_OP_CLEAR;
    //~ else if( initialLayoutColor == VK_IMAGE_LAYOUT_UNDEFINED )
        //~ lop = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    //~ else
        //~ lop = VK_ATTACHMENT_LOAD_OP_LOAD;
        
    for(unsigned i=0;i<(unsigned)numLayers;++i){
        attachmentDescriptions[i] = VkAttachmentDescription{
            .flags=0,
            .format = colorFormat,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = lop,
            .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
            .stencilLoadOp = lop,
            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE,
            .initialLayout = (lop==VK_ATTACHMENT_LOAD_OP_CLEAR || lop==VK_ATTACHMENT_LOAD_OP_DONT_CARE) ? VK_IMAGE_LAYOUT_UNDEFINED : initialLayoutColor, //VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout = finalLayoutColor
        };
    }
    
    attachmentDescriptions[numLayers] = VkAttachmentDescription{
        .flags=0,
        .format=depthFormat,
        .samples=VK_SAMPLE_COUNT_1_BIT,
        .loadOp=lop,
        .storeOp=VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp=lop,
        .stencilStoreOp=VK_ATTACHMENT_STORE_OP_STORE,
        .initialLayout= (lop==VK_ATTACHMENT_LOAD_OP_CLEAR || lop==VK_ATTACHMENT_LOAD_OP_DONT_CARE) ? VK_IMAGE_LAYOUT_UNDEFINED : initialLayoutDepth, //VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout=finalLayoutDepth
    };
    
    VkRenderPass renderPass;
    
    check(vkCreateRenderPass(
        ctx->dev,
        VkRenderPassCreateInfo{
            .sType=VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
            .pNext=nullptr,
            .flags=0,
            .attachmentCount=(unsigned)attachmentDescriptions.size(),
            .pAttachments = attachmentDescriptions.data(),
            .subpassCount = 1,
            .pSubpasses = &subpassDescription,
            .dependencyCount=1,
            .pDependencies = &subpassDependency
        }, 
        nullptr,
        &renderPass
    ));
    
    CleanupManager::registerCleanupFunction([ctx,renderPass](){
        vkDestroyRenderPass(ctx->dev,renderPass,nullptr);
    });
    
    ctx->setObjectName(renderPass,name);
    return renderPass;
}    

RenderPass::RenderPass(VulkanContext* ctx_, VkAttachmentLoadOp startingOp)
{
    this->name = "window renderpass";
    this->numLayers = 1;

    this->ctx=ctx_;
    VkImageLayout initialLayoutC;
    VkImageLayout initialLayoutDS;
    
    if( startingOp == VK_ATTACHMENT_LOAD_OP_LOAD ){
        //this is a secondary renderpass which can only
        //be used after some other renderpass has
        //drawn stuff initially
        initialLayoutC = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        initialLayoutDS = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    } else if( startingOp == VK_ATTACHMENT_LOAD_OP_CLEAR ){
        initialLayoutC = VK_IMAGE_LAYOUT_UNDEFINED;
        initialLayoutDS = VK_IMAGE_LAYOUT_UNDEFINED;
    } else if( startingOp == VK_ATTACHMENT_LOAD_OP_DONT_CARE ){
        initialLayoutC = VK_IMAGE_LAYOUT_UNDEFINED;
        initialLayoutDS = VK_IMAGE_LAYOUT_UNDEFINED;
    } else {
        assert(0);
        throw std::runtime_error("Bad starting op");
    }
    
    this->renderPass=make(ctx,
        ctx->surfaceFormat.format,
        1,
        ctx->depthFormat,
        initialLayoutC,
        initialLayoutDS,
        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        startingOp,
        this->name
    );
}
    
    
RenderPass::RenderPass(
    VulkanContext* ctx_,
    VkFormat colorFormat,
    int numLayers_,
    VkFormat depthFormat,
    VkImageLayout finalLayoutColor,
    VkImageLayout finalLayoutDepth,
    VkAttachmentLoadOp loadop,
    std::string name_)
{
    this->ctx=ctx_;
    this->numLayers = numLayers_;
    this->name=name_;
    this->renderPass = make(
        ctx,
        colorFormat,
        numLayers,
        depthFormat,
        finalLayoutColor,   //VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        finalLayoutDepth,   //VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        finalLayoutColor,
        finalLayoutDepth,   //VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
        loadop,name);
}


