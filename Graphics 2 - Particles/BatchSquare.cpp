
#include "BatchSquare.h"
#include "math2801.h"
#include "Samplers.h"
#include "Descriptors.h"
#include "Images.h"
#include "importantConstants.h"
#include <cassert>
#include <vector>

using namespace math2801;

BatchSquare::BatchSquare(VertexManager* vertexManager, vec2 size) {
    std::vector<vec3> p; //poses
    std::vector<vec2> t;  //texcoords
    std::vector<vec4> dummytangents;
    std::vector<std::uint32_t> indices;

    for (int i = 0; i < BATCH_SIZE; ++i) 
    {
        indices.push_back(i*4);
        indices.push_back(i*4+1);
        indices.push_back(i*4+2);
        indices.push_back(i*4);
        indices.push_back(i*4+2);
        indices.push_back(i*4+3);

        p.push_back(vec3(i,size.x,size.y));
        p.push_back(vec3(i, size.x, size.y));
        p.push_back(vec3(i, size.x, size.y));
        p.push_back(vec3(i, size.x, size.y));

        t.push_back(vec2(0,0));
        t.push_back(vec2(1, 0));
        t.push_back(vec2(1, 1));
        t.push_back(vec2(0, 1));

        dummytangents.push_back(vec4(0, 0, 0, 0));
        dummytangents.push_back(vec4(0, 0, 0, 0));
        dummytangents.push_back(vec4(0, 0, 0, 0));
        dummytangents.push_back(vec4(0, 0, 0, 0));
    }
    this->drawinfo = vertexManager->addIndexedData(
       indices,
        p,
        t,
        p,
        dummytangents,
        t
    );
}


void BatchSquare::drawInstanced(VkCommandBuffer cmd,
    unsigned numInstances)
{
    vkCmdDrawIndexed(
        cmd,
        6*BATCH_SIZE,              //index count
        numInstances,              //instance count
        this->drawinfo.indexOffset,
        this->drawinfo.vertexOffset,
        0               //first instance
    );
   
}