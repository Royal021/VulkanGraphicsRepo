#include "Framebuffer.h"
#include "ImageManager.h"
#include "Meshes.h"
#include "GraphicsPipeline.h"
#include "Descriptors.h"
#include "VertexManager.h"
#include "CleanupManager.h"
#include "ShaderManager.h"
#include "PushConstants.h"
#include "Samplers.h"
#include "utils.h"
#include <cmath>
#include <assert.h>

using namespace math2801;

static VulkanContext* ctx;
static std::vector<Framebuffer*> _allFramebuffers;

typedef std::tuple<int, int, VkFormat> FBKey;

//helper FB's for blurring. To save memory,
//we share helpers: They are keyed by
//width, height, and format. If two FB's have
//same w,h,fmt then they will share the same helper
static std::map<FBKey, Framebuffer*> blurHelpers;

//private vertex manager for blurring quads
static VertexManager* fbVertexManager;

//private push constants for blurring
static PushConstants* fbBlurPushConstants;

//private DSL for blur operations
static DescriptorSetLayout* fbBlurDescriptorSetLayout;

//private factory for blur operations
static DescriptorSetFactory* fbBlurDescriptorSetFactory;

//shaders for blurring. We could have used a compute shader
//too, but this works and we don't have to worry about switching
//which queue/pipe we're using. blurddfs = distance dependent blur fs
static VkPipelineShaderStageCreateInfo blurvs, blurfs, blurddfs;

//layout for blurring
static PipelineLayout* fbBlurPipelineLayout;

//vertex/index info for blur quad
static VertexManager::Info blurQuadInfo;

//128 bytes for push constants = 32 floats = 8 vec4's
static std::string blurPushConstantSrc =
"layout(push_constant,row_major) uniform pushConstants{\n"
"    uvec4 blurWeights[7];\n"
"    vec2 blurDelta;\n"
"    float blurMultiplier;\n"
"    uint blurLayerAndIterations;\n"
"};";

static std::string blurvsSrc = std::string(
    "#version 450 core\n"
    "layout(location=0) in vec2 position;\n"
    "layout(location=0) out vec2 v_texcoord;\n"
    "void main(){\n"
    "    gl_Position = vec4( 2.0*position-vec2(1.0), 0.0, 1.0 );\n"
    "    v_texcoord = position;\n"
    "}");


//this code is a bit more complex than it could be
//since we want to pack two weights into one 32 bit float
//so we can get twice the maximum radius
//This code is used for both distance dependent and non-distance dependent
//blur, with a conditional #define
static std::string blurfsSrc = std::string(
    "layout(location=0) in vec2 texcoord;                               \n"
    "layout(location=0) out vec4 color;                                 \n"
    "layout(set=0,binding=0) uniform sampler samp; //clamp,mip          \n"
    "layout(set=0,binding=1) uniform texture2DArray tex;                \n"
    "layout(set=0,binding=2) uniform sampler nsamp; //clamp, nearest    \n"
    "layout(set=0,binding=3) uniform texture2DArray depthBuffer;        \n"
) + blurPushConstantSrc + std::string(
    "                                                                   \n"
    "#line 84                                                           \n"
    "#if USE_DEPTH != 0                                                 \n"
    "void addPoint(                                                     \n"
    "        float weight, vec3 texc,                                   \n"
    "        float centerDepth, inout vec4 total,                       \n"
    "        inout float totalWeight )                                  \n"
    "{                                                                  \n"
    "    float d = texture(                                             \n"
    "        sampler2DArray(depthBuffer,nsamp),texc                     \n"
    "    ).r;                                                           \n"
    "    if( d < centerDepth )                                          \n"
    "        return;                                                    \n"
    "    total += weight * texture(                                     \n"
    "             sampler2DArray(tex,samp),                             \n"
    "             texc                                                  \n"
    "    );                                                             \n"
    "    totalWeight += weight;                                         \n"
    "}                                                                  \n"
    "#else                                                              \n"
    "void addPoint(float weight, vec3 texc,inout vec4 total)            \n"
    "{                                                                  \n"
    "    total += weight * texture(                                     \n"
    "             sampler2DArray(tex,samp),                             \n"
    "             texc                                                  \n"
    "    );                                                             \n"
    "}                                                                  \n"
    "#endif                                                             \n"
    "void main(){                                                       \n"
    "                                                                   \n"
    "   uint blurLayer = blurLayerAndIterations>>16;                    \n"
    "   uint blurIterations = blurLayerAndIterations & 0xffff;          \n"
    "                                                                   \n"
    "   vec3 t = vec3(texcoord,float(blurLayer));                       \n"
    "   vec4 total = vec4(0);                                           \n"
    "   vec3 t1 = t;  //tex coord to the right                          \n"
    "   vec3 t2 = t;  //tex coord to the left                           \n"
    "                                                                   \n"
    "   ivec2 texSize = textureSize(sampler2DArray(tex,samp),0).xy;     \n"
    "   vec2 delta = 1.0/texSize;                                       \n"
    "   delta *= blurDelta;                                             \n"
    "                                                                   \n"
    "   #if USE_DEPTH == 1                                              \n"
    "       float totalWeight=0.0;                                      \n"
    "       float centerDepth = texture(                                \n"
    "           sampler2DArray(depthBuffer,nsamp), t                    \n"
    "       ).r;                                                        \n"
    "       gl_FragDepth=centerDepth;                                   \n"
    "   #endif                                                          \n"
    "                                                                   \n"
    "   for(int i=0;i<7;++i){                                           \n"
    "       if( blurWeights[i] == uvec4(0) )                            \n"
    "           break;                                                  \n"
    "       for(int j=0;j<4;++j){                                       \n"
    "           uint tmp = blurWeights[i][j];                           \n"
    "           //sample point at center of kernel twice, but the       \n"
    "           //weight has already been scaled                        \n"
    "           //to be half of what it should be (cpu side), so it     \n"
    "           //all works out                                         \n"
    "           float w1 = float( tmp>>16 )/65535.0;                    \n"
    "           float w2 = float( tmp & 0xffff ) / 65535.0;             \n"
    "           #if USE_DEPTH == 1                                      \n"
    "               addPoint(w1,t1,centerDepth,total,totalWeight);      \n"
    "               addPoint(w1,t2,centerDepth,total,totalWeight);      \n"
    "           #else                                                   \n"
    "               addPoint(w1,t1,total);                              \n"
    "               addPoint(w1,t2,total);                              \n"
    "           #endif                                                  \n"
    "           t1.xy += delta;                                         \n"
    "           t2.xy -= delta;                                         \n"
    "           #if USE_DEPTH                                           \n"
    "               addPoint(w2,t1,centerDepth,total,totalWeight);      \n"
    "               addPoint(w2,t2,centerDepth,total,totalWeight);      \n"
    "           #else                                                   \n"
    "               addPoint(w2,t1,total);                              \n"
    "               addPoint(w2,t2,total);                              \n"
    "           #endif                                                  \n"
    "           t1.xy += delta;                                         \n"
    "           t2.xy -= delta;                                         \n"
    "       }                                                           \n"
    "   }                                                               \n"
    "   #if USE_DEPTH                                                   \n"
    "       total *= 1.0/totalWeight;                                   \n"
    "   #endif                                                          \n"
    "   color = total*blurMultiplier;                                   \n"
    "}                                                                  \n"
);

//~ "color.rgb=vec3(centerDepth); color.a=1.0; return;\n"


static int currentSwapchainIndex_ = -1;

static int currentSwapchainIndex() {
    if (currentSwapchainIndex_ == -1)
        throw std::runtime_error("Cannot use a framebuffer outside a frame draw operation");
    return currentSwapchainIndex_;
}

static void frameBegin(int imageIndex, VkCommandBuffer)
{
    currentSwapchainIndex_ = imageIndex;
}

static void frameEnd(int, VkCommandBuffer)
{
    currentSwapchainIndex_ = -1;
}

bool Framebuffer::initialized()
{
    return ctx != nullptr;
}

void Framebuffer::initialize(VulkanContext* ctx_)
{
    if (initialized())
        return;

    ctx = ctx_;
    ShaderManager::initialize(ctx);
    fbVertexManager = new VertexManager(
        ctx,
        {
            {.format = VK_FORMAT_R32G32_SFLOAT,   .rate = VK_VERTEX_INPUT_RATE_VERTEX }       //position
        }
    );

    blurQuadInfo = fbVertexManager->addIndexedData(
        { 0,1,2, 0,2,3 },
        std::vector<vec2>{ {0, 0}, { 0,1 }, { 1,1 }, { 1,0 } }
    );
    fbVertexManager->pushToGPU();

    fbBlurPushConstants = new PushConstants(blurPushConstantSrc);

    fbBlurDescriptorSetLayout = new DescriptorSetLayout(ctx,
        {
            {.type = VK_DESCRIPTOR_TYPE_SAMPLER,         .slot = 0   },
            {.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,   .slot = 1   },
            {.type = VK_DESCRIPTOR_TYPE_SAMPLER,         .slot = 2   },
            {.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,   .slot = 3   }
        }
    );

    fbBlurPipelineLayout = new PipelineLayout(
        ctx,
        fbBlurPushConstants,
        { fbBlurDescriptorSetLayout, nullptr, nullptr },
        "fbBlurPipelineLayout"
    );

    fbBlurDescriptorSetFactory = new DescriptorSetFactory(
        ctx, "FBOBlurDSFactory",
        0,      //binding point
        fbBlurPipelineLayout
    );

    blurvs = ShaderManager::loadFromString(blurvsSrc, "vert");
    blurfs = ShaderManager::loadFromString("#version 450 core\n#define USE_DEPTH 0\n" + blurfsSrc, "frag");
    blurddfs = ShaderManager::loadFromString("#version 450 core\n#define USE_DEPTH 1\n" + blurfsSrc, "frag");

    utils::registerFrameBeginCallback(frameBegin);
    utils::registerFrameEndCallback(frameEnd);

}

Framebuffer::Framebuffer()
{
    assert(ctx);

    //using default framebuffer
    this->width = ctx->width;
    this->height = ctx->height;
    this->allLayersFramebuffers = ctx->framebuffers;
    this->allLayersRenderPassDiscard = new RenderPass(ctx, VK_ATTACHMENT_LOAD_OP_DONT_CARE);
    this->allLayersRenderPassKeep = new RenderPass(ctx, VK_ATTACHMENT_LOAD_OP_LOAD);
    this->allLayersRenderPassClear = new RenderPass(ctx, VK_ATTACHMENT_LOAD_OP_CLEAR);
    this->singleLayerRenderPassDiscard = this->allLayersRenderPassDiscard;
    this->singleLayerRenderPassKeep = this->allLayersRenderPassKeep;
    this->singleLayerRenderPassClear = this->allLayersRenderPassClear;
    this->numLayers = 1;
    this->isDefaultFB = true;
    this->name = "Default Framebuffer";
    _allFramebuffers.push_back(this);
}

Framebuffer::~Framebuffer() {
}

Framebuffer::Framebuffer(unsigned w, unsigned h, unsigned layers, VkFormat format_, std::string name_)
    : Framebuffer(true, w, h, layers, format_, name_)
{}

Framebuffer::Framebuffer(bool blurrable, unsigned w, unsigned h, unsigned layers, VkFormat format_, std::string name_)
{
    assert(ctx);
    this->width = w;
    this->height = h;
    this->numLayers = layers;
    this->format = format_;
    this->name = name_;
    this->isDefaultFB = false;

    this->colorBuffers.reserve(ctx->numSwapchainImages);
    this->depthBuffers.reserve(ctx->numSwapchainImages);
    for (int i = 0; i < ctx->numSwapchainImages; ++i) {
        this->colorBuffers.push_back(
            ImageManager::createUninitializedImage(
                w, h, layers,
                format,
                VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                VK_IMAGE_VIEW_TYPE_2D_ARRAY,
                VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,   //final layout
                VK_IMAGE_ASPECT_COLOR_BIT,
                this->name + "[" + std::to_string(i) + "].color"
            )
        );
        this->depthBuffers.push_back(
            ImageManager::createUninitializedImage(
                w, h, 1,
                ctx->depthFormat,
                VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                VK_IMAGE_VIEW_TYPE_2D_ARRAY,
                VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,   //final layout VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
                VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT,
                this->name + "[" + std::to_string(i) + "].depth"
            )
        );
    }

    ImageManager::addCallback([this]() {
        this->pushToGPU();
        });

    unsigned clampedLayers = numLayers;
    if (numLayers > 8)
        clampedLayers = 8;
    this->allLayersRenderPassDiscard = new RenderPass(
        ctx,
        format,
        clampedLayers,
        ctx->depthFormat,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        "all layers renderpass for " + this->name
    );
    this->allLayersRenderPassKeep = new RenderPass(
        ctx,
        format,
        clampedLayers,
        ctx->depthFormat,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        VK_ATTACHMENT_LOAD_OP_LOAD,
        "all layers renderpass for " + this->name
    );
    this->allLayersRenderPassClear = new RenderPass(
        ctx,
        format,
        clampedLayers,
        ctx->depthFormat,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        VK_ATTACHMENT_LOAD_OP_CLEAR,
        "all layers renderpass for " + this->name
    );

    this->singleLayerRenderPassDiscard = new RenderPass(
        ctx,
        format,
        1,
        ctx->depthFormat,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        "single layer renderpass for " + this->name
    );
    this->singleLayerRenderPassKeep = new RenderPass(
        ctx,
        format,
        1,
        ctx->depthFormat,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        VK_ATTACHMENT_LOAD_OP_LOAD,
        "single layer renderpass for " + this->name
    );
    this->singleLayerRenderPassClear = new RenderPass(
        ctx,
        format,
        1,
        ctx->depthFormat,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        VK_ATTACHMENT_LOAD_OP_CLEAR,
        "single layer renderpass for " + this->name
    );
    _allFramebuffers.push_back(this);

    //even if this is not blurrable, we must still make a pipeline
    //for it since it might be a blur helper.

    //use blur shaders, use render pass discard, don't check or change depth buffer
    this->blurPipeline = (new GraphicsPipeline(
        ctx,
        fbBlurPipelineLayout,
        fbVertexManager->layout,
        this,
        "blurPipeline for " + this->name
    ))
        ->set(blurvs)
        ->set(blurfs)
        ->set(this->singleLayerRenderPassDiscard)
        ->set(VkPipelineDepthStencilStateCreateInfo{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .depthTestEnable = VK_FALSE,
            .depthWriteEnable = VK_FALSE,
            .depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,
            .depthBoundsTestEnable = VK_FALSE,
            .stencilTestEnable = VK_FALSE,
            .front = VkStencilOpState{
                .failOp = VK_STENCIL_OP_KEEP,
                .passOp = VK_STENCIL_OP_KEEP,
                .depthFailOp = VK_STENCIL_OP_KEEP,
                .compareOp = VK_COMPARE_OP_ALWAYS,
                .compareMask = 0xff,
                .writeMask = 0xff,
                .reference = 0
            },
            .back = VkStencilOpState{
                .failOp = VK_STENCIL_OP_KEEP,
                .passOp = VK_STENCIL_OP_KEEP,
                .depthFailOp = VK_STENCIL_OP_KEEP,
                .compareOp = VK_COMPARE_OP_ALWAYS,
                .compareMask = 0xff,
                .writeMask = 0xff,
                .reference = 0
            },
            .minDepthBounds = 0.0,
            .maxDepthBounds = 1.0
            });

    //use blur shaders, use render pass discard,
    //depth test always passes, depth writes enabled so
    //we can copy depth buffer to helper
    this->blurDDPipelineWriteToHelper = blurPipeline->clone("blurdd")
        ->set(blurddfs)
        ->set(VkPipelineDepthStencilStateCreateInfo{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .depthTestEnable = VK_TRUE,
            .depthWriteEnable = VK_TRUE,
            .depthCompareOp = VK_COMPARE_OP_ALWAYS,
            .depthBoundsTestEnable = VK_FALSE,
            .stencilTestEnable = VK_FALSE,
            .front = VkStencilOpState{
                .failOp = VK_STENCIL_OP_KEEP,
                .passOp = VK_STENCIL_OP_KEEP,
                .depthFailOp = VK_STENCIL_OP_KEEP,
                .compareOp = VK_COMPARE_OP_ALWAYS,
                .compareMask = 0xff,
                .writeMask = 0xff,
                .reference = 0
            },
            .back = VkStencilOpState{
                .failOp = VK_STENCIL_OP_KEEP,
                .passOp = VK_STENCIL_OP_KEEP,
                .depthFailOp = VK_STENCIL_OP_KEEP,
                .compareOp = VK_COMPARE_OP_ALWAYS,
                .compareMask = 0xff,
                .writeMask = 0xff,
                .reference = 0
            },
            .minDepthBounds = 0.0,
            .maxDepthBounds = 1.0
            });

    //use blur shaders, use render pass discard,
    //depth buffer not changed
    this->blurDDPipelineWriteToFB = blurPipeline->clone("blurddwtfb")
        ->set(blurddfs);

    if (blurrable) {
        FBKey k{ this->width, this->height, this->format };
        if (!blurHelpers.contains(k)) {
            blurHelpers[k] = new Framebuffer(
                false,
                this->width, this->height, 1,
                this->format, "blur helper");
        }
        this->blurHelper = blurHelpers[k];

        //blur descriptor sets are not created for helpers
        this->blurDescriptorSet = fbBlurDescriptorSetFactory->make();
    }
    else {
        this->blurHelper = nullptr;
        this->blurDescriptorSet = nullptr;
    }

    CleanupManager::registerCleanupFunction([this]() {
        for (VkFramebuffer F : this->allLayersFramebuffers) {
            vkDestroyFramebuffer(ctx->dev, F, nullptr);
        }
        for (std::vector<VkFramebuffer> L : this->singleLayerFramebuffers) {
            for (VkFramebuffer F : L) {
                vkDestroyFramebuffer(ctx->dev, F, nullptr);
            }
        }
        for (VkImageView v : this->depthBufferViews) {
            vkDestroyImageView(ctx->dev, v, nullptr);
        }
        });

}

void Framebuffer::pushToGPU()
{
    if (this->pushedToGPU)
        return;

    if (!this->isDefaultFB) {

        //first one is reserve, second is resize. Difference is important!
        this->allLayersFramebuffers.reserve(ctx->numSwapchainImages);
        this->singleLayerFramebuffers.resize(ctx->numSwapchainImages);

        for (int chainImageIndex = 0;
            chainImageIndex < ctx->numSwapchainImages;
            ++chainImageIndex)
        {
            Image* img = this->colorBuffers[chainImageIndex];
            {
                std::vector<VkImageView> views;
                for (unsigned j = 0; j < img->numLayers && j < 8; ++j) {
                    views.push_back(img->layers[j].view());
                }
                views.push_back(this->depthBuffers[chainImageIndex]->layers[0].view());
                VkFramebuffer fb;
                check(vkCreateFramebuffer(
                    ctx->dev,
                    VkFramebufferCreateInfo{
                        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                        .pNext = nullptr,
                        .flags = 0,
                        //VK spec 8.2: Load and store op's don't affect
                        //renderpass compatibility
                        .renderPass = this->allLayersRenderPassDiscard->renderPass,
                        .attachmentCount = (unsigned)views.size(),
                        .pAttachments = views.data(),
                        .width = (unsigned)this->width,
                        .height = (unsigned)this->height,
                        .layers = 1
                    },
                    nullptr,
                    &fb
                ));
                this->allLayersFramebuffers.push_back(fb);
            }

            {
                this->singleLayerFramebuffers[chainImageIndex].resize(img->numLayers);
                //now make views for one layer at a time
                for (unsigned j = 0; j < img->numLayers; ++j) {
                    std::vector<VkImageView> views;
                    views.push_back(img->layers[j].view());
                    views.push_back(this->depthBuffers[chainImageIndex]->layers[0].view());
                    VkFramebuffer fb;
                    check(vkCreateFramebuffer(
                        ctx->dev,
                        VkFramebufferCreateInfo{
                            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                            .pNext = nullptr,
                            .flags = 0,
                            //VK spec 8.2: This will be compatible with either
                            //clear or noclear renderpasses
                            .renderPass = this->singleLayerRenderPassDiscard->renderPass,
                            .attachmentCount = (unsigned)views.size(),
                            .pAttachments = views.data(),
                            .width = (unsigned)this->width,
                            .height = (unsigned)this->height,
                            .layers = 1
                        },
                        nullptr,
                        &fb
                    ));
                    this->singleLayerFramebuffers[chainImageIndex][j] = fb;
                }
            }
        }

        //make depth buffer views
        this->depthBufferViews.resize(this->depthBuffers.size());
        for (int i = 0; i < (int)this->depthBuffers.size(); ++i) {
            Image* D = this->depthBuffers[i];
            this->depthBufferViews[i] = D->createView(
                D->viewType, D->format, VK_IMAGE_ASPECT_DEPTH_BIT,
                0, 1, 0, 1, "depth aspect view");
        }
    }

    this->pushedToGPU = true;
}

void Framebuffer::beginRenderPassDiscardContents(VkCommandBuffer cmd) {
    int imageIndex = currentSwapchainIndex();
    this->beginRenderPassHelper(imageIndex, -1, cmd, VK_ATTACHMENT_LOAD_OP_DONT_CARE, 0.0f, 0.0f, 0.0f, 0.0f);
}

void Framebuffer::beginRenderPassKeepContents(VkCommandBuffer cmd)
{
    int imageIndex = currentSwapchainIndex();
    this->beginRenderPassHelper(imageIndex, -1, cmd, VK_ATTACHMENT_LOAD_OP_LOAD, 0.0f, 0.0f, 0.0f, 0.0f);
}

void Framebuffer::beginRenderPassClearContents(VkCommandBuffer cmd, float r, float g, float b, float a)
{
    int imageIndex = currentSwapchainIndex();
    this->beginRenderPassHelper(imageIndex, -1, cmd, VK_ATTACHMENT_LOAD_OP_CLEAR, r, g, b, a);
}

void Framebuffer::beginOneLayerRenderPassDiscardContents(int layerIndex, VkCommandBuffer cmd) {
    int imageIndex = currentSwapchainIndex();
    this->beginRenderPassHelper(imageIndex, layerIndex, cmd, VK_ATTACHMENT_LOAD_OP_DONT_CARE, 0.0f, 0.0f, 0.0f, 0.0f);
}

void Framebuffer::beginOneLayerRenderPassDiscardContentsWithIndex(int imageIndex, int layerIndex, VkCommandBuffer cmd) {
    this->beginRenderPassHelper(imageIndex, layerIndex, cmd, VK_ATTACHMENT_LOAD_OP_DONT_CARE, 0.0f, 0.0f, 0.0f, 0.0f);
}

void Framebuffer::beginOneLayerRenderPassKeepContentsWithIndex(int imageIndex, int layerIndex, VkCommandBuffer cmd) {
    this->beginRenderPassHelper(imageIndex, layerIndex, cmd, VK_ATTACHMENT_LOAD_OP_LOAD, 0.0f, 0.0f, 0.0f, 0.0f);
}

void Framebuffer::beginOneLayerRenderPassKeepContents(int layerIndex, VkCommandBuffer cmd)
{
    int imageIndex = currentSwapchainIndex();
    this->beginRenderPassHelper(imageIndex, layerIndex, cmd, VK_ATTACHMENT_LOAD_OP_LOAD, 0.0f, 0.0f, 0.0f, 0.0f);
}

void Framebuffer::beginOneLayerRenderPassClearContents(int layerIndex, VkCommandBuffer cmd,
    float r, float g, float b, float a)
{
    int imageIndex = currentSwapchainIndex();
    this->beginRenderPassHelper(imageIndex, layerIndex, cmd, VK_ATTACHMENT_LOAD_OP_CLEAR, r, g, b, a);
}


void Framebuffer::beginRenderPassHelper(int imageIndex, int layerIndex,
    VkCommandBuffer cmd, VkAttachmentLoadOp loadOp,
    float clearR, float clearG, float clearB, float clearA
) {

    std::string s = (
        std::string("renderPass: ") +
        this->name + ", imageIndex=" + std::to_string(imageIndex) +
        (
            layerIndex == -1 ?
            (std::string(" all layers")) :
            (std::string(" layer ") + std::to_string(layerIndex))
            )
        );
    ctx->beginCmdRegion(cmd, s);

    assert(imageIndex >= 0);
    assert(imageIndex < ctx->numSwapchainImages);

    if (!(layerIndex == -1 || (layerIndex >= 0 && layerIndex < (int)this->numLayers))) {
        if (this->numLayers == 1) {
            throw std::runtime_error("Bad layer (" + std::to_string(layerIndex) +
                ") for Framebuffer::beginRenderPass [" + this->name + "]; must be -1 or 0");
        }
        else {
            throw std::runtime_error("Bad layer (" + std::to_string(layerIndex) +
                ") for Framebuffer::beginRenderPass [" + this->name + "]; must be -1 or " +
                "in range [0..." + std::to_string(this->numLayers - 1) + "]");
        }
    }

    int numLayersToDraw = ((layerIndex == -1) ? this->numLayers : 1);

    if (this->insideRenderpass) {
        throw std::runtime_error("Cannot begin a new renderpass while we're still in another renderpass");
    }
    this->insideRenderpass = true;
    this->currentRenderIndex = imageIndex;

    if (!this->isDefaultFB) {

        if (!this->allLayersFramebuffers.size()) {
            throw std::runtime_error("Framebuffer::beginRenderPass() called, but Framebuffer hasn't been pushed to GPU yet");
        }

        this->colorBuffers[imageIndex]->layoutTransition(
            //~ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
            cmd
        );

        this->depthBuffers[imageIndex]->layoutTransition(
            //~ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
            cmd
        );
    }

    std::vector<VkClearValue> clearValues;
    if (loadOp == VK_ATTACHMENT_LOAD_OP_CLEAR) {
        VkClearValue tmp;
        tmp.color.float32[0] = clearR;
        tmp.color.float32[1] = clearG;
        tmp.color.float32[2] = clearB;
        tmp.color.float32[3] = clearA;
        clearValues.resize(numLayersToDraw, tmp);
        tmp.depthStencil.depth = 1.0f;
        tmp.depthStencil.stencil = 0;
        clearValues.push_back(tmp);
    }
    RenderPass* rp;
    if (layerIndex == -1) {
        //draw all layers
        switch (loadOp) {
        case VK_ATTACHMENT_LOAD_OP_DONT_CARE:   rp = allLayersRenderPassDiscard; break;
        case VK_ATTACHMENT_LOAD_OP_LOAD:        rp = allLayersRenderPassKeep; break;
        case VK_ATTACHMENT_LOAD_OP_CLEAR:       rp = allLayersRenderPassClear; break;
        default: assert(0); throw std::runtime_error("Error");
        }
    }
    else {
        switch (loadOp) {
        case VK_ATTACHMENT_LOAD_OP_DONT_CARE:   rp = singleLayerRenderPassDiscard; break;
        case VK_ATTACHMENT_LOAD_OP_LOAD:        rp = singleLayerRenderPassKeep; break;
        case VK_ATTACHMENT_LOAD_OP_CLEAR:       rp = singleLayerRenderPassClear; break;
        default: assert(0); throw std::runtime_error("Error");
        }
    }

    vkCmdBeginRenderPass(
        cmd,
        VkRenderPassBeginInfo{
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .pNext = nullptr,
            .renderPass = rp->renderPass,
            .framebuffer = ((layerIndex == -1) ? this->allLayersFramebuffers[imageIndex] : this->singleLayerFramebuffers[imageIndex][layerIndex]),
            .renderArea = VkRect2D{
                .offset = VkOffset2D{
                    .x = 0,
                    .y = 0
                },
                .extent = VkExtent2D{
                    .width = (unsigned)this->width,
                    .height = (unsigned)this->height
                }
            },
            .clearValueCount = (unsigned)clearValues.size(),
            .pClearValues = (clearValues.empty() ? nullptr : clearValues.data())
        },
        VK_SUBPASS_CONTENTS_INLINE
    );

}
void Framebuffer::endRenderPassNoMipmaps(VkCommandBuffer cmd)
{
    if (!this->insideRenderpass) {
        throw std::runtime_error("endRenderPass() called while not in a renderpass");
    }

    ctx->endCmdRegion(cmd);

    vkCmdEndRenderPass(cmd);
    this->insideRenderpass = false;

    this->completedRenderIndex = this->currentRenderIndex;
    this->currentRenderIndex = -1;

    if (!this->isDefaultFB) {
        this->colorBuffers[this->completedRenderIndex]->layoutTransition(
            //~ VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, //VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            cmd
        );

        this->depthBuffers[this->completedRenderIndex]->layoutTransition(
            //~ VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            cmd
        );
    }
}

void Framebuffer::endRenderPass(VkCommandBuffer cmd)
{

    if (!this->insideRenderpass) {
        throw std::runtime_error("endRenderPass() called while not in a renderpass");
    }

    ctx->endCmdRegion(cmd);

    vkCmdEndRenderPass(cmd);
    this->insideRenderpass = false;

    this->completedRenderIndex = this->currentRenderIndex;
    this->currentRenderIndex = -1;

    if (!this->isDefaultFB) {
        ctx->beginCmdRegion(cmd, "Computing mipmaps index=" + std::to_string(this->completedRenderIndex));

        //build mipmaps
        Image* img = this->colorBuffers[this->completedRenderIndex];

        //process each layer
        for (unsigned layerNum = 0; layerNum < img->numLayers; ++layerNum) {

            //read from layer 0
            img->layoutTransition(
                layerNum, 0,
                //~ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                cmd
            );

            for (int mipLevel = 1; mipLevel < (int)img->layers[0].mips.size(); ++mipLevel) {
                //write to layer mipLevel
                img->layoutTransition(
                    layerNum, mipLevel,
                    //~ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                    cmd
                );

                VkImageBlit region{
                    .srcSubresource = {
                        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                        .mipLevel = (unsigned)mipLevel - 1,
                        .baseArrayLayer = (unsigned)layerNum,
                        .layerCount = 1
                    },
                    .srcOffsets = {
                        {.x = 0, .y = 0, .z = 0 },
                        {
                            .x = (int)img->layers[layerNum].mips[mipLevel - 1].width,
                            .y = (int)img->layers[layerNum].mips[mipLevel - 1].height,
                            .z = 1
                        }
                    },
                    .dstSubresource = {
                        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                        .mipLevel = (unsigned)mipLevel,
                        .baseArrayLayer = (unsigned)layerNum,
                        .layerCount = 1
                    },
                    .dstOffsets = {
                        {.x = 0, .y = 0, .z = 0 },
                        {
                            .x = (int)img->layers[layerNum].mips[mipLevel].width,
                            .y = (int)img->layers[layerNum].mips[mipLevel].height,
                            .z = 1
                        }
                    }
                };

                vkCmdBlitImage(
                    cmd,
                    img->image,
                    VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                    img->image,
                    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                    1,
                    &region,
                    VK_FILTER_LINEAR
                );

                //prepare level for reading on the next round
                img->layoutTransition(
                    layerNum, mipLevel,
                    //~ VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                    VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                    cmd
                );
            }
        }

        this->colorBuffers[this->completedRenderIndex]->layoutTransition(
            //~ VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, //VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            cmd
        );

        this->depthBuffers[this->completedRenderIndex]->layoutTransition(
            //~ VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            cmd
        );

        ctx->endCmdRegion(cmd);
    }
}

void Framebuffer::clear(VkCommandBuffer cmd, float r, float g, float b, float a)
{
    VkClearColorValue cc;
    cc.float32[0] = r;
    cc.float32[1] = g;
    cc.float32[2] = b;
    cc.float32[3] = a;
    this->clear(cmd, cc, 1.0f, 0);
}


void Framebuffer::clear(VkCommandBuffer cmd,
    std::optional<VkClearColorValue> clearColorValue,
    std::optional<float> clearDepthValue,
    std::optional<std::uint32_t> clearStencilValue
) {
    std::vector<VkClearAttachment> clears;
    clears.reserve(this->numLayers + 1);

    if (clearColorValue.has_value()) {
        clears.resize(this->numLayers);
        for (unsigned i = 0; i < this->numLayers; ++i) {
            clears[i].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            clears[i].colorAttachment = i;
            clears[i].clearValue.color = clearColorValue.value();
            //~ clears[i].clearValue.color.float32[0] = r;
            //~ clears[i].clearValue.color.float32[1] = g;
            //~ clears[i].clearValue.color.float32[2] = b;
            //~ clears[i].clearValue.color.float32[3] = a;
        }
    }

    if (clearDepthValue.has_value() || clearStencilValue.has_value()) {
        clears.resize(clears.size() + 1);
        clears.back().aspectMask = (clearDepthValue.has_value() ? VK_IMAGE_ASPECT_DEPTH_BIT : 0);
        clears.back().aspectMask |= (clearStencilValue.has_value() ? VK_IMAGE_ASPECT_STENCIL_BIT : 0);
        clears.back().colorAttachment = 0;    //ignored
        clears.back().clearValue.depthStencil = VkClearDepthStencilValue{
            .depth = (clearDepthValue.has_value() ? clearDepthValue.value() : 1.0f),
            .stencil = (clearStencilValue.has_value() ? clearStencilValue.value() : 0)
        };
    }

    VkClearRect rect{
        .rect = {
            .offset = {
                .x = 0,
                .y = 0
            },
            .extent = {
                .width = (unsigned)this->width,
                .height = (unsigned)this->height
            }
        },
        .baseArrayLayer = 0,
        .layerCount = 1           //from the spec, it appears this is applied to each attachment in turn
    };

    vkCmdClearAttachments(
        cmd,
        (unsigned)clears.size(),
        clears.data(),
        1,
        &rect
    );
}

//~ void Framebuffer::forEachImage( std::function<void(int,Image*,Image*)> callback ){
    //~ assert(this->colorBuffers.size() == this->depthBuffers.size() );

    //~ //FIXME: If multiple images, need to change this
    //~ for(int ii=0;ii<(int)colorBuffers.size();++ii){
        //~ callback( ii, this->colorBuffers[ii], this->depthBuffers[ii] );
    //~ }
//~ }

//FIXME: Also need to restore per-frame descriptor set
void Framebuffer::blur(unsigned radius, unsigned layer,
    float multiplier, VkCommandBuffer cmd, VertexManager* oldVM)
{
    this->blur(radius, layer, multiplier, cmd, oldVM, false);
}

void Framebuffer::blur(unsigned radius, unsigned layer,
    float multiplier, VkCommandBuffer cmd, VertexManager* oldVM,
    bool doDistanceDependentBlur)
{

    ctx->beginCmdRegion(cmd, "Blur");
    fbVertexManager->bindBuffers(cmd);

    if (layer >= this->numLayers) {
        if (this->numLayers == 1)
            throw std::runtime_error("Bad layer number for blur (" + std::to_string(layer) + "): This Framebuffer only has 1 layer\n");
        else
            throw std::runtime_error("Bad layer number for blur (" + std::to_string(layer) + "): Must be between 0 and " + std::to_string(this->numLayers));
    }

    if (this->insideRenderpass) {
        throw std::runtime_error("Cannot blur a framebuffer while it is the render destination");
    }

    if (this->completedRenderIndex == -1) {
        throw std::runtime_error("Cannot blur framebuffer: You have not yet rendered to it");
    }

    if (!this->blurHelper) {
        throw std::runtime_error("Cannot blur the window's framebuffer");
    }

    //we pack two weights per uint, so
    //n uvec4's give us n*8 weights
    //This gives us a maximum blur radius of 56
    //since we have 7 uvec4's available in the push constants
    static std::map<int, std::vector<uvec4> > weights;
    std::map<int, std::vector<uvec4> >::iterator witer;
    witer = weights.find(radius);
    if (witer == weights.end()) {
        std::vector<uvec4> wi;
        wi.resize(7, { 0,0,0,0 });
        std::vector<float> F(wi.size() * 4 * 2);
        if (radius > (unsigned)F.size()) {
            throw std::runtime_error("Blur radius (" + std::to_string(radius) + ") is too large");
        }
        float sigma = float(radius) / 3.0f;
        float sum = 0.0f;
        for (unsigned i = 0; i < radius; ++i) {
            float Q = float((i * i) / (-2.0 * sigma * sigma));
            float wt = float(exp(Q) / (sigma * sqrt(2.0 * 3.14159265358979323)));
            //special case; we process kernel center twice in shader so we halve the weight
            if (i == 0)
                wt *= 0.5f;
            assert(wt < 1.0f);
            sum += wt + wt;       //double slot 0 too since we apply it twice and we halved it above
            F[i] = wt;
        }
        float s = 1.0f / sum;
        for (int i = 0, j = 0, k = 0; i < (int)F.size(); i += 2) {
            float f1 = F[i] * s;
            float f2 = F[i + 1] * s;
            unsigned u1 = unsigned(f1 * 65535 + 0.5);
            assert(u1 < 65536);
            unsigned u2 = unsigned(f2 * 65535 + 0.5);
            assert(u2 < 65536);
            wi[j][k] = unsigned((u1 << 16) | u2);
            k++;
            j += (k / 4);
            k %= 4;
        }
        double ss = 0.0;
        for (auto u : wi) {
            for (int xx = 0; xx < 4; ++xx) {
                double ff = (u[xx] >> 16) / 65535.0 * 2;
                ss += ff;
                ff = (u[xx] & 0xffff) / 65535.0 * 2;
                ss += ff;
            }
        }
        weights[radius] = wi;
        witer = weights.find(radius);
    }

    ctx->insertCmdLabel(cmd, "Begin blur");

    assert(this->completedRenderIndex != -1);
    this->blurHelper->beginOneLayerRenderPassDiscardContentsWithIndex(this->completedRenderIndex, 0, cmd);

    //write to the blurHelper FBO
    if (doDistanceDependentBlur) {
        this->blurHelper->blurDDPipelineWriteToHelper->use(cmd);
    }
    else {
        this->blurHelper->blurPipeline->use(cmd);
    }

    //kernel width = 1 + blurWidth*4*2
    //in other words, we always have at least one element
    //and then we do blurWidth*4 elements to the left & right.
    //To get kernel of arbitrary size, pad blurWeights with zeros.
    fbBlurPushConstants->set(cmd, "blurMultiplier", multiplier);
    //FIXME: iteration count is too pessimistic
    fbBlurPushConstants->set(cmd, "blurLayerAndIterations", (layer << 16) | (radius / 2 + 1));
    fbBlurPushConstants->set(cmd, "blurWeights", witer->second);
    fbBlurPushConstants->set(cmd, "blurDelta", vec2(1.0f, 0.0f));


    //read from this FBO
    this->blurDescriptorSet->setSlot(0, Samplers::clampingMipSampler);
    this->blurDescriptorSet->setSlot(1, this->colorBuffers[this->completedRenderIndex]->view());
    this->blurDescriptorSet->setSlot(2, Samplers::nearestSampler);
    this->blurDescriptorSet->setSlot(3, this->depthBufferViews[this->completedRenderIndex]);
    this->blurDescriptorSet->bind(cmd);

    //draw the quad
    vkCmdDrawIndexed(
        cmd,
        blurQuadInfo.numIndices,
        1,              //instance count
        blurQuadInfo.indexOffset,
        blurQuadInfo.vertexOffset,
        0               //first instance
    );

    this->blurHelper->endRenderPass(cmd);

    //this->beginOneLayerRenderPassDiscardContentsWithIndex(this->completedRenderIndex,layer,cmd);
    this->beginOneLayerRenderPassKeepContentsWithIndex(this->completedRenderIndex, layer, cmd);
    fbBlurPushConstants->set(cmd, "blurDelta", vec2(0.0f, 1.0f));
    //FIXME: iterations is too pessimistic
    fbBlurPushConstants->set(cmd, "blurLayerAndIterations", radius / 2 + 1);

    //write to this fbo
    if (doDistanceDependentBlur) {
        this->blurDDPipelineWriteToFB->use(cmd);
    }
    else {
        this->blurPipeline->use(cmd);
    }

    //~ this->blurDescriptorSet->setSlot(0,Samplers::clampingMipSampler);
    this->blurDescriptorSet->setSlot(1, this->blurHelper->colorBuffers[this->completedRenderIndex]->view());
    //~ this->blurDescriptorSet->setSlot(2,Samplers::nearestSampler);
    this->blurDescriptorSet->setSlot(3, this->blurHelper->depthBufferViews[this->completedRenderIndex]);
    this->blurDescriptorSet->bind(cmd);


    //read from the blur helper
    //~ this->blurHelper->blurDescriptorSets[this->lastRenderedImage]->bind(cmd);

    vkCmdDrawIndexed(
        cmd,
        blurQuadInfo.numIndices,
        1,              //instance count
        blurQuadInfo.indexOffset,
        blurQuadInfo.vertexOffset,
        0               //first instance
    );


    ctx->insertCmdLabel(cmd, "End blur");

    this->endRenderPass(cmd);


    if (oldVM)
        oldVM->bindBuffers(cmd);
    ctx->endCmdRegion(cmd);

}

Image* Framebuffer::currentImage()
{
    if (this->completedRenderIndex == -1)
        throw std::runtime_error("Framebuffer has not been rendered to");
    if (this->isDefaultFB)
        throw std::runtime_error("Cannot get image from default framebuffer");
    return this->colorBuffers[this->completedRenderIndex];
}

VkImageView Framebuffer::currentDepthBufferView()
{
    if (this->completedRenderIndex == -1)
        throw std::runtime_error("Framebuffer has not been rendered to");
    if (this->isDefaultFB)
        throw std::runtime_error("Cannot get image from default framebuffer");
    return this->depthBufferViews[this->completedRenderIndex];
}