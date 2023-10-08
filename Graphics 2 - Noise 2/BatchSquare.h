#pragma once
#include "vkhelpers.h"
#include "VertexManager.h"

class VertexManager;
class DescriptorSet;
class Image;

class BatchSquare {
public:
    VertexManager::Info drawinfo;
    BatchSquare(VertexManager* vertexManager);
    void drawInstanced(VkCommandBuffer cmd, unsigned numInstances);
    BatchSquare(const BatchSquare&) = delete;
    void operator=(const BatchSquare&) = delete;
};
