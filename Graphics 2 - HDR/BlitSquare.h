#pragma once
#include "vkhelpers.h"
#include "VertexManager.h"

class VertexManager;
class DescriptorSet;
class Image;

class BlitSquare {
public:
    VertexManager::Info drawinfo;
    BlitSquare(VertexManager* vertexManager);
    void draw(VkCommandBuffer cmd, DescriptorSet* descriptorSet, Image* img);

    BlitSquare(const BlitSquare&) = delete;
    void operator=(const BlitSquare&) = delete;
};
