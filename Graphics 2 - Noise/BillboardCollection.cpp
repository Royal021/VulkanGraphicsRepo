#include "BillboardCollection.h"
#include "VertexManager.h"
#include "Buffers.h"
#include "BatchSquare.h"
#include "Descriptors.h"
#include "Samplers.h"
#include "Images.h"
#include "importantConstants.h"
#include "CleanupManager.h"

BillboardCollection::BillboardCollection(
    VulkanContext* ctx,
    VertexManager* vertexManager,
    const std::vector<math2801::vec4>& positions_,
    math2801::vec2 size,
    Image* img_)
{
    this->positions = new DeviceLocalBuffer(ctx, positions_,
        VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT |
        VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
        "BillboardCollection positions"
    );

    this->positionView = this->positions->makeView(
        VK_FORMAT_R32G32B32A32_SFLOAT
    );

    this->img = img_;
    this->numBillboards = (unsigned)positions_.size();
    this->batchSquare = new BatchSquare(vertexManager, size);
    

    CleanupManager::registerCleanupFunction([this, ctx]() {
        this->positions->cleanup();
        vkDestroyBufferView(ctx->dev, this->positionView, nullptr);
        });
}

void BillboardCollection::draw(VkCommandBuffer cmd,
    DescriptorSet* descriptorSet)
{
    descriptorSet->setSlot(BASE_TEXTURE_SAMPLER_SLOT, Samplers::mipSampler);
    descriptorSet->setSlot(BASE_TEXTURE_SLOT, this->img->view());
    descriptorSet->setSlot(BILLBOARD_TEXTURE_SLOT, this->positionView);
    descriptorSet->bind(cmd);
    this->batchSquare->drawInstanced(cmd, this->numBillboards/BATCH_SIZE);
}