#include "VertexManager.h"
#include "Buffers.h"
#include <cassert>
#include "utils.h"
#include "mischelpers.h"
#include "VertexInput.h"
#include "CleanupManager.h"

VertexManager::VertexManager(VulkanContext* ctx_, std::vector<VertexInput> inputs)
{
    this->ctx=ctx_;
    unsigned binding=0;
    for(auto& input: inputs){

        VkVertexInputAttributeDescription attribdesc{
            .location=binding,     //shader input location
            .binding=binding,      //binding number for sourcing data
            .format=input.format,
            .offset=0
        };
        this->vertexInputAttributeDescriptions.push_back(attribdesc);

        VkVertexInputBindingDescription desc;
        switch(input.format){
            case VK_FORMAT_R32_SFLOAT:
                desc.stride=4;
                break;
            case VK_FORMAT_R32G32_SFLOAT:
                desc.stride=8;
                break;
            case VK_FORMAT_R32G32B32_SFLOAT:
                desc.stride=12;
                break;
            case VK_FORMAT_R32G32B32A32_SFLOAT:
                desc.stride=16;
                break;
            default:
                throw std::runtime_error("Bad format for vertex input");
        }
        desc.inputRate = input.rate;
        desc.binding=binding++;

        this->vertexInputBindingDescriptions.push_back(desc);
    }

    this->layout = VkPipelineVertexInputStateCreateInfo{
        .sType=VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .pNext=nullptr,
        .flags=0,
        .vertexBindingDescriptionCount = (unsigned)vertexInputBindingDescriptions.size(),
        .pVertexBindingDescriptions = vertexInputBindingDescriptions.data(),
        .vertexAttributeDescriptionCount = (unsigned)vertexInputAttributeDescriptions.size(),
        .pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data()
    };

    this->bufferDatas.resize(vertexInputBindingDescriptions.size());

    CleanupManager::registerCleanupFunction( [this](){
        for(auto& b : this->buffers ){
            b->cleanup();
            delete b;
        }
        if(this->indexBuffer){
            this->indexBuffer->cleanup();
            delete this->indexBuffer;
        }
    });
}

VertexManager::Info VertexManager::addIndexedDataHelper3(
    const std::vector<std::uint32_t>& indices,
    std::vector< VertexManager::AttribInfo >& V )
{
    if( pushedToGPU ){
        throw std::runtime_error("Cannot add data after VertexManager::pushToGPU() was called");
    }

    if( V.size() != this->bufferDatas.size() ){
        throw std::runtime_error("VertexManager::addIndexedData: Expected to get "+
            std::to_string(this->bufferDatas.size())+" attributes, but got "+
            std::to_string(V.size()));
    }

    unsigned numv = numVertices;
    unsigned numi = (unsigned) indexData.size();

    for(int i=0;i<(int)V.size();++i){
        if( V[i].elementSize != vertexInputBindingDescriptions[i].stride ){
            throw std::runtime_error("Wrong type for indexed data input " + std::to_string(i) + ": Each element should be " +
                std::to_string(vertexInputBindingDescriptions[i].stride)+" bytes but each element was actually "+
                std::to_string(V[i].elementSize)+" bytes");
        }
        if( V[i].numElements != V[0].numElements ){
            throw std::runtime_error("Mismatched count for indexed data: Got "+
                std::to_string(V[i].numElements)+" elements but expected "+
                std::to_string(V[0].numElements)+" elements");
        }

        const char* p = (const char*)(V[i].ptr);
        this->bufferDatas[i].insert( this->bufferDatas[i].end(),
            p, p+V[i].elementSize*V[i].numElements
        );
    }

    numVertices += V[0].numElements;

    indexData.insert(indexData.end(),indices.begin(),indices.end());

    Info info;
    info.vertexOffset=numv;
    info.indexOffset=numi;
    info.numIndices=(int)indices.size();
    return info;
}

void VertexManager::pushToGPU()
{
    if(pushedToGPU){
        throw std::runtime_error("VertexManager::pushToGPU() called twice");
    }
    pushedToGPU=true;
    if( this->bufferDatas[0].empty() ){
        throw std::runtime_error("No vertex data?");
    }
    this->buffers.reserve(this->bufferDatas.size());
    for(int i=0;i<(int)this->bufferDatas.size();++i){
        assert(this->bufferDatas[i].size()>0);
        this->buffers.push_back(new DeviceLocalBuffer(
            ctx,
            this->bufferDatas[i],
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            "vertex attribute "+std::to_string(i)
        ));
    }
    this->indexBuffer = new DeviceLocalBuffer(
        this->ctx,
        this->indexData,
        VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        "indices");
}

void VertexManager::bindBuffers(VkCommandBuffer cmd)
{
    if(!pushedToGPU)
        throw std::runtime_error("Need to call VertexManager::pushToGPU() before calling bindBuffers()");

    std::vector<VkBuffer> tmp;
    tmp.reserve(this->buffers.size());
    std::vector<VkDeviceSize> offsets(this->buffers.size());      //automatically zeroed
    for(auto& b : this->buffers ){
        tmp.push_back(b->buffer);
    }

    vkCmdBindVertexBuffers(
        cmd,
        0,      //first binding
        (unsigned)tmp.size(),      //num bindings
        tmp.data(),
        offsets.data()
    );

    vkCmdBindIndexBuffer(
        cmd,
        this->indexBuffer->buffer,
        0,      //offset
        VK_INDEX_TYPE_UINT32
    );
}


