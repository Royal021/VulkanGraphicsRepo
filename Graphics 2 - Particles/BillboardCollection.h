#pragma once

#include "vkhelpers.h"
#include "math2801.h"

class BatchSquare;
class Buffer;
class Image;
class DescriptorSet;
class VertexManager;

class BillboardCollection {
public:

    BillboardCollection(
        VulkanContext* ctx,
        VertexManager* vertexManager,
        const std::vector<math2801::vec4>& positions,
        math2801::vec2 size,
        Image* img
    );
    void draw(VkCommandBuffer cmd, DescriptorSet* descriptorSet);
    
    unsigned numBillboards;
    Image* img;
    BatchSquare* batchSquare;
    VkBufferView positionView;
    Buffer* positions;
};