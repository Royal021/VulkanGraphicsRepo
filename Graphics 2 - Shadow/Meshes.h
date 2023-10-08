#pragma once
#include "vkhelpers.h"
#include "VertexManager.h"
#include "Images.h"
#include "math2801.h"
#include <span>

class PushConstants;
class Pipeline;
class DescriptorSetFactory;
class DescriptorSet;

namespace gltf{
    class GLTFScene;
};

/// A Primitive is a collection of geometry with the same material properties.
class Primitive{
  public:
    
    /// Information for the draw operation: Where the
    /// mesh data is located in memory
    VertexManager::Info drawinfo;
    
    /// Base color for object. See baseColorFactor.
    Image* baseColorTexture;
    
    /// Multiplied by color in baseColorTexture to get final 
    /// object color
    math2801::vec4 baseColorFactor;
    
    /// Emissive texture for object. See emissiveColorFactor
    Image* emissiveTexture;
    
    /// Multiplied by color in emissiveTexture to get final
    /// emissive color.
    math2801::vec3 emissiveColorFactor;

    Image* normalTexture;
    float normalFactor;

    /// Initialize the primitive.
    /// @param vertexManager VertexManager that will hold this 
    ///        Primitive's data
    /// @param positions Positions of primitive vertices
    /// @param textureCoordinates Texture coordinates for vertices.
    ///        textureCoordinates.size() must match positions.size() 
    /// @param normals Normals for vertices. normals.size() must
    ///        match positions.size() 
    /// @param indices Indices of triangles.
    /// @param baseColorTexture Base object color
    /// @param baseColorFactor Base color factor: Multiplied by color
    ///        in baseColorTexture to get final object color.
    /// @param emissiveTexture Emissive texture.
    /// @param emissiveColorFactor Multiplied by color in
    ///        emissiveTexture to get final emissive color.
    Primitive(
        VertexManager* vertexManager,
        const std::vector<math2801::vec3>& positions,
        const std::vector<math2801::vec2>& textureCoordinates,
        const std::vector<math2801::vec3>& normals,
        const std::vector<math2801::vec4>& tangents,
        const std::vector<math2801::vec2> textureCoordinates2,
        const std::vector<std::uint32_t>& indices,
        Image* baseColorTexture_,
        math2801::vec4 baseColorFactor_,
        Image* emissiveTexture_,
        math2801::vec3 emissiveColorFactor_,
        Image* normalTexture_,
        float normalFactor_
    );
    
    /// Draw the Primitive
    /// @param cmd The command buffer
    /// @param descriptorSet Descriptor set; will be updated
    ///        to hold references to Primitive's textures and
    ///        then bound for the draw operation
    /// @param pushConstants Push constants to hold baseColorFactor
    ///        and emissiveColorFactor
    void draw(VkCommandBuffer cmd, DescriptorSet* descriptorSet,
                PushConstants* pushConstants);

  private:
    Primitive(const Primitive&) = delete;
    void operator=(const Primitive&) = delete;

};

class Mesh{
    public:
    
    /// name
    std::string name;
    
    /// list of Primitives that make up this mesh
    std::vector<Primitive*> primitives;
    
    /// world matrix for the mesh
    math2801::mat4 worldMatrix;
    
    /// Create empty mesh
    Mesh();
    
    /// Create empty mesh
    /// @param name Name of the mesh
    Mesh(std::string name);
    
    /// Draw all Primitives in this Mesh.
    /// @param cmd The command buffer
    /// @param descriptorSet Descriptor set; will be updated
    ///        to hold references to Primitive's textures and
    ///        then bound for the draw operation
    /// @param pushConstants Push constants to hold baseColorFact
    void draw(VkCommandBuffer cmd, DescriptorSet* descriptorSet, PushConstants* pushConstants);
    
    /// Add a Primitive to the Mesh
    /// @param m The primitive
    void addPrimitive(Primitive* m);
    
    
    Mesh(const Mesh&) = delete;
    void operator=(const Mesh&) = delete;
    
};

namespace Meshes{

/// Extract all GLTFMeshes from a scene and return list of them
/// @param vertexManager Vertex manager for meshes
/// @param scene The GLTF scene to extract from
/// @return List of meshes
std::vector<Mesh*> getFromGLTF(VertexManager* vertexManager, 
        const gltf::GLTFScene& scene);

};

