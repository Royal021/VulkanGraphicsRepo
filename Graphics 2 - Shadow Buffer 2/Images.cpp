#include "vkhelpers.h"
#include "imagedecode.h"
#include "imagescale.h"
#include "CommandBuffer.h"
#include "utils.h"
#include "Images.h"
#include <cstring>
#include <fstream>
#include <cassert>
#include "Buffers.h"
#include "CleanupManager.h"
#include <iostream>
#include <array>

static VulkanContext* ctx;


static const char* stringForImageLayout(VkImageLayout layout)
{
    switch (layout) {
    case VK_IMAGE_LAYOUT_UNDEFINED: return "VK_IMAGE_LAYOUT_UNDEFINED";
    case VK_IMAGE_LAYOUT_GENERAL: return "VK_IMAGE_LAYOUT_GENERAL";
    case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL: return "VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL";
    case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL: return "VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL";
    case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL: return "VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL";
    case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL: return "VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL";
    case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL: return "VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL";
    case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL: return "VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL";
    case VK_IMAGE_LAYOUT_PREINITIALIZED: return "VK_IMAGE_LAYOUT_PREINITIALIZED";
    default: return "Unknown layout";
    }
}


namespace Images {

    bool initialized()
    {
        return ctx != nullptr;
    }

    void initialize(VulkanContext* ctx_)
    {
        if (initialized())
            return;
        ctx = ctx_;
    }

    Mip::Mip(int w, int h, std::span<const char> pixels_) {
        assert(w > 0);
        assert(w < 32768);
        assert(h > 0);
        assert(h < 32768);

        this->width = w;
        this->height = h;
        //note: pixels might be empty
        this->pixels.insert(this->pixels.end(), pixels_.begin(), pixels_.end());
    }

    Layer::Layer(int w, int h, std::span<const char> pixels) {
        assert(w > 0);
        assert(w < 32768);
        assert(h > 0);
        assert(h < 32768);

        this->width = w;
        this->height = h;
        this->mips.push_back(Mip(w, h, pixels));  //note: pixels might be empty
        this->makeMipPyramid();
    }

    VkImageView Layer::view() {
        if (!this->view_) {
            throw std::runtime_error("Request for image layer view, but image has not been pushed to GPU");
        }
        return this->view_;
    }

    void Layer::makeMipPyramid() {

        //~ if( this->mips.back().pixels.empty() ){
            //~ return;
        //~ }

        while (this->mips.back().width > 1 || this->mips.back().height > 1) {
            int sw = int(this->mips.back().width / 2);
            if (sw == 0)
                sw = 1;
            int sh = int(this->mips.back().height / 2);
            if (sh == 0)
                sh = 1;

            if (this->mips.back().pixels.empty()) {
                this->mips.push_back(Mip(sw, sh, std::vector<char>()));
            }
            else {
                std::vector<char> spix = imagescale::scaleImage(
                    this->mips.back().width,
                    this->mips.back().height,
                    this->mips.back().pixels,
                    sw, sh);
                this->mips.push_back(Mip(sw, sh, spix));
            }
        }
    }

}; //namespace


using Images::Layer;
using Images::Mip;

Image::Image(
    unsigned width_, unsigned height_, unsigned numLayers_,
    VkFormat format_, VkImageUsageFlags usage,
    VkImageCreateFlags flags, VkImageViewType viewType_,
    VkImageLayout finalLayout_, VkImageAspectFlags aspect_,
    const std::vector< std::span<const char> >& pixels,
    std::string name_
) {

    this->name = name_;
    this->numLayers = numLayers_;
    this->width = width_;
    this->height = height_;
    this->view_ = VK_NULL_HANDLE;
    this->format = format_;
    this->viewType = viewType_;
    this->finalLayout = finalLayout_;  //usually VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    this->aspect = aspect_;            //usually VK_IMAGE_ASPECT_COLOR_BIT

    assert(width > 0);
    assert(width < 32768);
    assert(height > 0);
    assert(height < 32768);
    assert(ctx);

    if (pixels.empty()) {
        for (unsigned i = 0; i < numLayers; ++i) {
            this->layers.push_back(Layer(width, height, std::span<const char>()));
        }
    }
    else {
        assert(numLayers == (unsigned)pixels.size());
        for (std::span<const char> pix : pixels) {
            this->layers.push_back(Layer(width, height, pix));
        }
    }

    check(vkCreateImage(
        ctx->dev,
        VkImageCreateInfo{
            .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .pNext = nullptr,
            .flags = flags,
            .imageType = VK_IMAGE_TYPE_2D,
            .format = this->format,
            .extent = VkExtent3D{
                .width = (unsigned)this->width,
                .height = (unsigned)this->height,
                .depth = 1,
            },
            .mipLevels = unsigned(this->layers[0].mips.size()),
            .arrayLayers = (unsigned)this->numLayers,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .tiling = VK_IMAGE_TILING_OPTIMAL,
            .usage = usage,
            .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
            .queueFamilyIndexCount = 0,
            .pQueueFamilyIndices = nullptr,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
        },
        nullptr,
        &(this->image)
    ));

    ctx->setObjectName(this->image, name);

    vkGetImageMemoryRequirements(
        ctx->dev,
        this->image,
        &(this->memoryRequirements)
    );

    CleanupManager::registerCleanupFunction([this]() {
        this->cleanup();
        });

}

void Image::cleanup() {
    assert(ctx);
    if (this->view_)
        vkDestroyImageView(ctx->dev, this->view_, nullptr);
    for (auto& L : this->layers) {
        if (L.view_)
            vkDestroyImageView(ctx->dev, L.view_, nullptr);
    }
    vkDestroyImage(ctx->dev, this->image, nullptr);
}

VkImageView Image::view() {
    if (!this->view_)
        throw std::runtime_error("Request for Image view, but you haven't called ImageManager::pushToGPU yet");
    return this->view_;
}

bool Image::pushedToGPU() {
    return this->view_ != VK_NULL_HANDLE;
}


VkImageView Image::createView(VkImageViewType viewType_, VkFormat format_,
    VkImageAspectFlags aspect_, unsigned firstMip, unsigned numMips,
    unsigned firstLayer, unsigned numLayers_,
    const std::string& name_)
{
    VkImageView view;
    check(vkCreateImageView(
        ctx->dev,
        VkImageViewCreateInfo{
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .image = this->image,
            .viewType = viewType_,
            .format = format_,
            .components = VkComponentMapping{
                .r = VK_COMPONENT_SWIZZLE_IDENTITY,
                .g = VK_COMPONENT_SWIZZLE_IDENTITY,
                .b = VK_COMPONENT_SWIZZLE_IDENTITY,
                .a = VK_COMPONENT_SWIZZLE_IDENTITY
            },
            .subresourceRange = VkImageSubresourceRange{
                .aspectMask = aspect_,
                .baseMipLevel = firstMip,
                .levelCount = numMips,
                .baseArrayLayer = firstLayer,
                .layerCount = numLayers_
            }
        },
        nullptr,
        &view
    ));
    ctx->setObjectName(view, name_);
    return view;
}


void Image::copyDataToGPU(StagingBuffer* stagingBuffer, VkDeviceMemory memory, VkDeviceSize startingOffset)
{
    assert(ctx);

    if (this->view_ != VK_NULL_HANDLE) {
        throw std::runtime_error("You have already pushed this image to the GPU; you cannot push it again");
    }

    check(vkBindImageMemory(
        ctx->dev,
        this->image,
        memory,
        startingOffset
    ));


    this->layoutTransition(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);


    if (this->layers[0].mips[0].pixels.empty()) {
        //no initial data, so nothing to copy
    }
    else if (this->aspect & VK_IMAGE_ASPECT_DEPTH_BIT) {
        throw std::runtime_error("Unimplemented: Depth texture with initial data...");
    }
    else {
        for (int layernumber = 0; layernumber < (int)this->layers.size(); ++layernumber) {
            Layer& layerdata = this->layers[layernumber];
            for (int miplevel = 0; miplevel < (int)layerdata.mips.size(); ++miplevel) {
                Mip& mipdata = layerdata.mips[miplevel];

                void* p = stagingBuffer->map();
                std::memcpy(p, mipdata.pixels.data(), mipdata.pixels.size() * sizeof(mipdata.pixels[0]));
                stagingBuffer->unmap();

                auto cmd = CommandBuffer::beginImmediateCommands();
                vkCmdCopyBufferToImage(
                    cmd,
                    stagingBuffer->buffer,
                    this->image,
                    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                    1,
                    VkBufferImageCopy{
                        .bufferOffset = 0,
                        .bufferRowLength = 0,      //0=no padding
                        .bufferImageHeight = 0,    //0=no padding
                        .imageSubresource = VkImageSubresourceLayers{
                            .aspectMask = this->aspect, //VK_IMAGE_ASPECT_COLOR_BIT,
                            .mipLevel = (unsigned)miplevel,
                            .baseArrayLayer = (unsigned)layernumber,
                            .layerCount = 1
                        },
                        .imageOffset = VkOffset3D{
                            .x = 0,
                            .y = 0,
                            .z = 0,
                        },
                        .imageExtent = VkExtent3D{
                            .width = (unsigned)mipdata.width,
                            .height = (unsigned)mipdata.height,
                            .depth = 1
                        }
                    }
                );
                CommandBuffer::endImmediateCommands(cmd);
            }
        }
    }

    this->layoutTransition(this->finalLayout);

    this->view_ = this->createView(
        this->viewType,
        this->format, this->aspect,
        0, unsigned(this->layers[0].mips.size()),
        0, (unsigned)this->numLayers,
        "image " + this->name + " all layers"
    );

    for (int i = 0; i < (int)this->layers.size(); ++i) {
        this->layers[i].view_ = this->createView(
            VK_IMAGE_VIEW_TYPE_2D,
            this->format, this->aspect,
            0, 1, (unsigned)i, 1,
            "image " + this->name + " layer " + std::to_string(i)
        );
    }

    for (auto& callback : this->callbacks) {
        callback(this);
    }

}

void Image::addCallback(std::function<void(Image*)> f) {
    if (this->view_ != VK_NULL_HANDLE) {
        //can call immediately
        f(this);
    }
    else {
        this->callbacks.push_back(f);
    }
}


void Image::layoutTransition(VkImageLayout newLayout_)
{
    auto cmd = CommandBuffer::beginImmediateCommands();
    this->layoutTransition(0, (unsigned)this->layers.size(),
        0, (unsigned)this->layers[0].mips.size(),
        newLayout_, cmd);
    CommandBuffer::endImmediateCommands(cmd);
}

void Image::layoutTransition(VkImageLayout newLayout_, VkCommandBuffer cmd)
{
    this->layoutTransition(0, (unsigned)this->layers.size(),
        0, (unsigned)this->layers[0].mips.size(),
        newLayout_, cmd);
}

void Image::layoutTransition(unsigned layer, unsigned mipLevel, VkImageLayout newLayout_)
{
    auto cmd = CommandBuffer::beginImmediateCommands();
    this->layoutTransition(layer, 1, mipLevel, 1, newLayout_, cmd);
    CommandBuffer::endImmediateCommands(cmd);
}

void Image::layoutTransition(
    unsigned layer,
    unsigned mipLevel,
    VkImageLayout newLayout_,
    VkCommandBuffer cmd
) {
    this->layoutTransition(layer, 1, mipLevel, 1, newLayout_, cmd);
}

bool Image::allLayoutsMatch(unsigned firstLayer, unsigned numLayersToCheck,
    unsigned firstMip, unsigned numMips)
{
    unsigned lastLayer = firstLayer + numLayersToCheck;
    unsigned lastMip = firstMip + numMips;
    VkImageLayout tmp = this->layers[firstLayer].mips[firstMip].layout;
    for (unsigned li = firstLayer; li < lastLayer; ++li) {
        for (unsigned mi = firstMip; mi < lastMip; ++mi) {
            if (this->layers[li].mips[mi].layout != tmp) {
                return false;
            }
        }
    }
    return true;
}

static void doBarrier(VkCommandBuffer cmd, VkImageAspectFlags aspect,
    VkImageLayout oldLayout, VkImageLayout newLayout,
    const std::array<unsigned, 4>& items,
    VkImage image
) {
    //do a layout transition even if new == old
    //so we can get the memory barrier

    unsigned firstLayer = items[0];
    unsigned numLayers = items[1];
    unsigned firstMip = items[2];
    unsigned numMips = items[3];

    ctx->insertCmdLabel(cmd, "barrier layers:", firstLayer, numLayers, "mips:", firstMip, numMips, "from",
        stringForImageLayout(oldLayout), "to", stringForImageLayout(newLayout));

    VkImageMemoryBarrier B{
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .pNext = nullptr,
        .srcAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT,
        .dstAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT,
        .oldLayout = oldLayout,
        .newLayout = newLayout,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .image = image,
        .subresourceRange = VkImageSubresourceRange{
            .aspectMask = aspect, //VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel = firstMip,
            .levelCount = numMips,
            .baseArrayLayer = firstLayer,
            .layerCount = numLayers
        }
    };

    vkCmdPipelineBarrier(
        cmd,
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
        0,
        0, nullptr,    //memory barriers
        0, nullptr,    //buffer barriers
        1,
        &B
    );
}

void Image::layoutTransition(unsigned firstLayer, unsigned numLayersToTransition,
    unsigned firstMip, unsigned numMips,
    VkImageLayout newLayout, VkCommandBuffer cmd)
{
    this->layoutTransition(this->aspect, firstLayer, numLayersToTransition,
        firstMip, numMips, newLayout, cmd);
}

const char* stringForAspect(VkImageAspectFlags aspect)
{
    switch (aspect) {
    case VK_IMAGE_ASPECT_COLOR_BIT:
        return "VK_IMAGE_ASPECT_COLOR_BIT";
    case VK_IMAGE_ASPECT_DEPTH_BIT:
        return "VK_IMAGE_ASPECT_DEPTH_BIT";
    case VK_IMAGE_ASPECT_STENCIL_BIT:
        return "VK_IMAGE_ASPECT_STENCIL_BIT";
    case VK_IMAGE_ASPECT_COLOR_BIT | VK_IMAGE_ASPECT_DEPTH_BIT:
        return "VK_IMAGE_ASPECT_{COLOR,DEPTH}_BIT";
    case VK_IMAGE_ASPECT_COLOR_BIT | VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT:
        return "VK_IMAGE_ASPECT_{COLOR,DEPTH,STENCIL}_BIT";
    case VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT:
        return "VK_IMAGE_ASPECT_{DEPTH,STENCIL}_BIT";
    default:
        return "Unknown aspect";
    }
}

void Image::layoutTransition(
    VkImageAspectFlags aspectForTransition,
    unsigned firstLayer, unsigned numLayersToTransition,
    unsigned firstMip, unsigned numMips,
    VkImageLayout newLayout,
    VkCommandBuffer cmd
) {
    unsigned lastLayer = firstLayer + numLayersToTransition;
    unsigned lastMip = firstMip + numMips;

    std::string s = this->name + ": layout transition: layer";
    if (numLayersToTransition != 1) {
        s += "s ";
        s += std::to_string(firstLayer);
        s += " to ";
        s += std::to_string(firstLayer + numLayersToTransition - 1);
    }
    else {
        s += " ";
        s += std::to_string(firstLayer);
    }
    s += ", mip";
    if (numMips != 1) {
        s += "s ";
        s += std::to_string(firstMip);
        s += " to ";
        s += std::to_string(firstMip + numMips - 1);
    }
    else {
        s += " ";
        s += std::to_string(firstMip);
    }
    s += " ";
    s += stringForImageLayout(newLayout);
    s += " ";
    s += stringForAspect(aspectForTransition);

    ctx->insertCmdLabel(cmd, s);

    assert(lastLayer <= (unsigned)this->layers.size());
    assert(lastMip <= (unsigned)this->layers[0].mips.size());

    if (this->allLayoutsMatch(firstLayer, numLayersToTransition, firstMip, numMips)) {
        //if the entire image has the same format,
        //transition the whole thing in one operation
        doBarrier(cmd, aspectForTransition, this->layers[firstLayer].mips[firstMip].layout,
            newLayout, { firstLayer, numLayersToTransition, firstMip, numMips },
            this->image
        );
    }
    else {
        for (unsigned li = firstLayer; li < lastLayer; li++) {
            //if all mips of the layer have the same format,
            //add it to the list in one chunk
            if (this->allLayoutsMatch(li, 1, firstMip, numMips)) {
                doBarrier(cmd, aspectForTransition, this->layers[li].mips[firstMip].layout,
                    newLayout, { li,1, firstMip, numMips }, this->image
                );
            }
            else {
                //slow path: do mips one at a time
                for (unsigned mi = firstMip; mi < lastMip; ++mi) {
                    doBarrier(cmd, aspectForTransition, this->layers[li].mips[mi].layout,
                        newLayout, { li,1,mi,1 }, this->image);
                }
            }
        }
    }

    for (unsigned li = firstLayer; li < lastLayer; li++) {
        for (unsigned mi = firstMip; mi < lastMip; mi++) {
            this->layers[li].mips[mi].layout = newLayout;
        }
    }

}

