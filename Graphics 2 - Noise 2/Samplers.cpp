#include "Samplers.h"
#include "CleanupManager.h"


static VulkanContext* ctx;


static VkSampler _make(VkFilter minMagFilter, VkSamplerAddressMode repeatMode, bool useMipmap)
{
    VkSampler samp;
    check(
        vkCreateSampler(
            ctx->dev,
            VkSamplerCreateInfo{
                .sType=VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                .pNext=nullptr,
                .flags=0,
                .magFilter=minMagFilter,
                .minFilter=minMagFilter,
                .mipmapMode=VK_SAMPLER_MIPMAP_MODE_LINEAR,
                .addressModeU = repeatMode,
                .addressModeV = repeatMode,
                .addressModeW = repeatMode,
                .mipLodBias=0,
                .anisotropyEnable=(useMipmap ? VK_TRUE : VK_FALSE),
                .maxAnisotropy=4,
                .compareEnable=VK_FALSE,
                .compareOp=VK_COMPARE_OP_ALWAYS,
                .minLod=0,
                .maxLod=( useMipmap ? VK_LOD_CLAMP_NONE : 0 ),
                .borderColor=VK_BORDER_COLOR_INT_OPAQUE_BLACK,
                .unnormalizedCoordinates=VK_FALSE,
            },
            nullptr,
            &(samp)
    ));
    return samp;
}



namespace Samplers{

VkSampler nearestSampler ;
VkSampler linearSampler  ;
VkSampler mipSampler     ;
VkSampler clampingMipSampler     ;


bool initialized()
{
    return ctx != nullptr;
}

void initialize(VulkanContext* ctx_){

    if(initialized())
        return;

    ctx=ctx_;
    Samplers::nearestSampler = _make(
        VK_FILTER_NEAREST,
        VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
        false
    );
    Samplers::linearSampler = _make(
        VK_FILTER_LINEAR,
        VK_SAMPLER_ADDRESS_MODE_REPEAT,
        false
    );
    Samplers::mipSampler = _make(
        VK_FILTER_LINEAR,
        VK_SAMPLER_ADDRESS_MODE_REPEAT,
        true
    );
    Samplers::clampingMipSampler = _make(
        VK_FILTER_LINEAR,
        VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
        true
    );

    CleanupManager::registerCleanupFunction(
        [](){
        vkDestroySampler(
            ctx->dev,
            Samplers::nearestSampler,
            nullptr
        );

        vkDestroySampler(
            ctx->dev,
            Samplers::linearSampler,
            nullptr
        );

        vkDestroySampler(
            ctx->dev,
            Samplers::mipSampler,
            nullptr
        );

        vkDestroySampler(
            ctx->dev,
            Samplers::clampingMipSampler,
            nullptr
        );
    });
}


}; //namespace
