#include "Meshes.h"
#include "Descriptors.h"
#include "VertexManager.h"
#include "Samplers.h"
#include "PushConstants.h"
#include "gltf.h"
#include "ImageManager.h"
#include "Pipeline.h"
#include "importantConstants.h"


Primitive::Primitive(
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
){
    this->drawinfo = vertexManager->addIndexedData( 
            indices,
            positions,
            textureCoordinates,
            normals,
            tangents,
            textureCoordinates2
            
    );
    this->baseColorTexture = baseColorTexture_;
    this->baseColorFactor=baseColorFactor_;
    this->emissiveTexture = emissiveTexture_;
    this->emissiveColorFactor = emissiveColorFactor_;
    this->normalTexture = normalTexture_;
    this->normalFactor = normalFactor_;
}

void Primitive::draw(VkCommandBuffer cmd, DescriptorSet* descriptorSet, PushConstants* pushConstants)
{
    descriptorSet->setSlot(BASE_TEXTURE_SAMPLER_SLOT, Samplers::mipSampler );
    descriptorSet->setSlot(BASE_TEXTURE_SLOT, baseColorTexture->view() );
    descriptorSet->setSlot(EMISSIVE_TEXTURE_SLOT, emissiveTexture->view() );
    descriptorSet->setSlot(NORMAL_TEXTURE_SLOT, normalTexture->view());
    descriptorSet->bind(cmd);
    pushConstants->set(cmd,"baseColorFactor",this->baseColorFactor);
    pushConstants->set(cmd,"emissiveFactor",this->emissiveColorFactor);
    pushConstants->set(cmd, "normalFactor", this->normalFactor);
    vkCmdDrawIndexed(
        cmd,
        this->drawinfo.numIndices,
        1,              //instance count
        this->drawinfo.indexOffset,
        this->drawinfo.vertexOffset,
        0               //first instance
    );
}
 

Mesh::Mesh(std::string name_)
{
    this->name=name_;
    this->worldMatrix=math2801::mat4::identity();
}

Mesh::Mesh()
{
    this->name="anonymous mesh";
    this->worldMatrix=math2801::mat4::identity();
}


void Mesh::draw(VkCommandBuffer cmd, DescriptorSet* descriptorSet, PushConstants* pushConstants)
{
    pushConstants->set(cmd,"worldMatrix", this->worldMatrix);
    for(auto& p : this->primitives ){
        p->draw(cmd,descriptorSet,pushConstants);
    }
}
 
void Mesh::addPrimitive(Primitive* m)
{
    this->primitives.push_back(m);
}


namespace Meshes {

std::vector<Mesh*> getFromGLTF(VertexManager* vertexManager, const gltf::GLTFScene& scene)
{
    std::vector<Mesh*> meshes;
    
    for(const gltf::GLTFMesh& gmesh : scene.meshes){
        meshes.push_back(new Mesh(gmesh.name));
        meshes.back()->worldMatrix=gmesh.matrix;
        for(const gltf::GLTFPrimitive& p : gmesh.primitives ){
            
            Image* baseColorTexture;
            std::string imagename = p.material.pbrMetallicRoughness.baseColorTexture.texture.source.name;
            auto tmp = p.material.pbrMetallicRoughness.baseColorTexture.texture.source.bytes;
            baseColorTexture = ImageManager::loadFromData(tmp,imagename);
            
            Image* emissiveTexture;
            imagename = p.material.emissiveTexture.texture.source.name;
            tmp = p.material.emissiveTexture.texture.source.bytes;
            emissiveTexture = ImageManager::loadFromData(tmp,imagename);

            Image* normalTexture;
            imagename = p.material.normalTexture.texture.source.name;
            tmp = p.material.normalTexture.texture.source.bytes;
            normalTexture = ImageManager::loadFromData(tmp, imagename);
            
            meshes.back()->addPrimitive(new Primitive(
                vertexManager,
                p.positions,
                p.textureCoordinates,
                p.normals,
                p.tangents,
                p.textureCoordinates2,
                p.indices,
                baseColorTexture,
                p.material.pbrMetallicRoughness.baseColorFactor,
                emissiveTexture,
                p.material.emissiveFactor,
                normalTexture,
                p.material.normalTexture.scale
            ));
        }
    }
    return meshes;
}
      

};
