#include "BlitSquare.h"
#include "math2801.h"
#include "Samplers.h"
#include "Descriptors.h"
#include "Images.h"
#include "importantConstants.h"
#include <cassert>
#include <vector>

using namespace math2801;

BlitSquare::BlitSquare(VertexManager* vertexManager) {
    this->drawinfo = vertexManager->addIndexedData(

        //indices
        { 0,1,2, 0,2,3 },

        //positions
        std::vector<vec3>{vec3{ -1,-1,0 }, vec3{ 1,-1,0 },
        vec3{ 1,1,0 }, vec3{ -1,1,0 }},

        //texcoord 1
        std::vector<vec2>{ {0, 0}, { 1,0 }, { 1,1 }, { 0,1 } },

        //normal (dummy)
        std::vector<vec3>{ {0, 0, 1}, { 0,0,1 }, { 0,0,1 },
        { 0,0,1 } },

        //tangent (dummy)
        std::vector<vec4>{ {0, 0, 0, 0}, { 0,0,0,0 },
        { 0,0,0,0 }, { 0,0,0,0 } },

        //texcoord 2 (dummy)
        std::vector<vec2>{ {0, 0}, { 1,0 }, { 1,1 }, { 0,1 } }
    );
}

void BlitSquare::draw(VkCommandBuffer cmd,
    DescriptorSet* descriptorSet, Image* img)
{
    if (img != nullptr) {
        descriptorSet->setSlot(BASE_TEXTURE_SAMPLER_SLOT,
            Samplers::clampingMipSampler);
        descriptorSet->setSlot(BASE_TEXTURE_SLOT, img->view());

        //these three are dummy
        descriptorSet->setSlot(EMISSIVE_TEXTURE_SLOT, img->view());
        descriptorSet->setSlot(NORMAL_TEXTURE_SLOT, img->view());
        descriptorSet->setSlot(METALLICROUGHNESS_TEXTURE_SLOT, img->view());

        descriptorSet->bind(cmd);
    }
    vkCmdDrawIndexed(
        cmd,
        6,              //index count
        1,              //instance count
        this->drawinfo.indexOffset,
        this->drawinfo.vertexOffset,
        0               //first instance
    );
}

void BlitSquare::drawInstanced(VkCommandBuffer cmd,
    unsigned numInstances)
{
    vkCmdDrawIndexed(
        cmd,
        6,              //index count
        numInstances,              //instance count
        this->drawinfo.indexOffset,
        this->drawinfo.vertexOffset,
        0               //first instance
    );
}