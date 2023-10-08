#pragma once
#include "vkhelpers.h"
#include "math2801.h"
#include "VertexInput.h"

class DeviceLocalBuffer;

/// Class to manage vertex and index data for all meshes.
class VertexManager{
  public:

    /// Create vertex manager
    /// @param ctx The context
    /// @param inputs Describes the inputs for each vertex
    VertexManager(VulkanContext* ctx, std::vector<VertexInput> inputs);

    /// When data is added, an Info structure is returned
    /// so the caller can draw the geometry that has
    /// just been handed to the VertexManager.
    struct Info{
        /// Offset of the vertex data in the VertexManager's buffer
        unsigned vertexOffset;
        /// Offset of the index data in the VertexManager's buffer
        unsigned indexOffset;
        /// Number of indices to draw
        unsigned numIndices;
    };

    /// The vertex layout
    VkPipelineVertexInputStateCreateInfo layout;
    
    /// Add indexed data
    /// @param indices The indices
    /// @param args The position, texture coordinate, etc. These
    ///     must be specified in the same order as the
    ///     VertexInput items passed to the constructor.
    /// @return An Info structure describing the newly added data.
    template<typename ...T>
    Info addIndexedData(const std::vector<std::uint32_t>& indices, T... args ){
        return addIndexedDataHelper(indices, args...);
    }

    /// Transfer all vertex data to the GPU. This can only be called once.
    void pushToGPU();
    
    /// Bind the vertex buffers for rendering
    /// @param cmd The command buffer
    void bindBuffers(VkCommandBuffer cmd);
    
  private:
  
    VulkanContext* ctx;
    
    struct AttribInfo{
        const void* ptr;
        unsigned numElements;
        unsigned elementSize;
    };
    
    template<typename ...T>
    Info addIndexedDataHelper(const std::vector<std::uint32_t>& indices, T... args){
        std::vector< AttribInfo > V;
        return addIndexedDataHelper2( indices, V, args... );
    }
    
    template<typename ...T>
    Info addIndexedDataHelper2(const std::vector<std::uint32_t>& indices, 
                               std::vector< AttribInfo >&  V, 
                               const std::vector<float>& data, 
                               T... args){
        AttribInfo ai{data.data(), (unsigned)data.size(), (unsigned)sizeof(float) };
        V.push_back( ai );
        return addIndexedDataHelper2( indices, V, args... );
    }
    template<typename ...T>
    Info addIndexedDataHelper2(const std::vector<std::uint32_t>& indices, 
                               std::vector< AttribInfo >&  V, 
                               const std::vector<math2801::vec2>& data, 
                               T... args){
        AttribInfo ai{data.data(), (unsigned)data.size(), (unsigned)sizeof(math2801::vec2) }   ;                                
        V.push_back( ai );
        return addIndexedDataHelper2( indices, V, args... );
    }  
    template<typename ...T>
    Info addIndexedDataHelper2(const std::vector<std::uint32_t>& indices, 
                               std::vector< AttribInfo >&  V, 
                               const std::vector<math2801::vec3>& data, 
                               T... args){
        AttribInfo ai{data.data(), (unsigned)data.size(), (unsigned)sizeof(math2801::vec3) };
        V.push_back( ai );
        return addIndexedDataHelper2( indices, V, args... );
    }  
        template<typename ...T>
    Info addIndexedDataHelper2(const std::vector<std::uint32_t>& indices, 
                               std::vector< AttribInfo >&  V, 
                               const std::vector<math2801::vec4>& data, 
                               T... args){
        AttribInfo ai{data.data(), (unsigned)data.size(), (unsigned)sizeof(math2801::vec4) };
        V.push_back( ai );
        return addIndexedDataHelper2( indices, V, args... );
    } 
    Info addIndexedDataHelper2(const std::vector<std::uint32_t>& indices, 
                               std::vector< AttribInfo >&  V, 
                               const std::vector<float>& data){
        AttribInfo ai{data.data(), (unsigned)data.size(), (unsigned)sizeof(float) };
        V.push_back( ai );
        return addIndexedDataHelper3( indices, V );
    }
    Info addIndexedDataHelper2(const std::vector<std::uint32_t>& indices, 
                               std::vector< AttribInfo >&  V, 
                               const std::vector<math2801::vec2>& data){
        AttribInfo ai{data.data(), (unsigned)data.size(), (unsigned)sizeof(math2801::vec2) };
        V.push_back( ai );
        return addIndexedDataHelper3( indices, V );
    }  
    Info addIndexedDataHelper2(const std::vector<std::uint32_t>& indices, 
                               std::vector< AttribInfo >&  V, 
                               const std::vector<math2801::vec3>& data){ 
        AttribInfo ai{data.data(), (unsigned)data.size(), (unsigned)sizeof(math2801::vec3) };
        V.push_back( ai );
        return addIndexedDataHelper3( indices, V );
    }  
    Info addIndexedDataHelper2(const std::vector<std::uint32_t>& indices, 
                               std::vector< AttribInfo >&  V, 
                               const std::vector<math2801::vec4>& data){
        AttribInfo ai{data.data(), (unsigned)data.size(), (unsigned)sizeof(math2801::vec4) };
        V.push_back( ai );
        return addIndexedDataHelper3( indices, V );
    }  
 
    Info addIndexedDataHelper3(const std::vector<std::uint32_t>& indices, std::vector< AttribInfo >& V );
    VertexManager(const VertexManager&) = delete;
    void operator=(const VertexManager&) = delete;
    
    std::vector<DeviceLocalBuffer*> buffers;
    std::vector< std::vector<char> > bufferDatas;
    DeviceLocalBuffer* indexBuffer=nullptr;
    std::vector<std::uint32_t> indexData;
    
    std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions;

    unsigned numVertices=0;
    bool pushedToGPU=false;
};
 
