#include "vkhelpers.h"
#include "Globals.h"
#include "ShaderManager.h"
#include "importantConstants.h"
#include "Uniforms.h"
#include "ImageManager.h"
#include "gltf.h"
#include "GraphicsPipeline.h"
#include <SDL.h>

using namespace math2801;
  
void setup(Globals& globs)
{
    globs.keepLooping=true;
    globs.framebuffer = new Framebuffer();
    
    globs.vertexManager = new VertexManager(
        globs.ctx,
        {
            { .format=VK_FORMAT_R32G32B32_SFLOAT,   .rate=VK_VERTEX_INPUT_RATE_VERTEX },  //position
            { .format=VK_FORMAT_R32G32_SFLOAT,      .rate=VK_VERTEX_INPUT_RATE_VERTEX },  //texcoord
            { .format=VK_FORMAT_R32G32B32_SFLOAT,   .rate=VK_VERTEX_INPUT_RATE_VERTEX },   //normal
            { .format=VK_FORMAT_R32G32B32A32_SFLOAT, .rate=VK_VERTEX_INPUT_RATE_VERTEX },  // tangent
            {.format = VK_FORMAT_R32G32_SFLOAT,      .rate = VK_VERTEX_INPUT_RATE_VERTEX } //TEX2
        }
    );
    
    globs.pushConstants = new PushConstants("shaders/pushconstants.txt");
    
    globs.descriptorSetLayout = new DescriptorSetLayout(
        globs.ctx,
        {
            { .type=VK_DESCRIPTOR_TYPE_SAMPLER,           .slot=BASE_TEXTURE_SAMPLER_SLOT },
            { .type=VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,     .slot=BASE_TEXTURE_SLOT         },
            { .type=VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,     .slot=EMISSIVE_TEXTURE_SLOT     },
            { .type=VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,    .slot=UNIFORM_BUFFER_SLOT       },
            {.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,    .slot = NORMAL_TEXTURE_SLOT     },
            {.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,    .slot = METALLICROUGHNESS_TEXTURE_SLOT    },
             {.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,   .slot = ENVMAP_TEXTURE_SLOT  },

        }
    );
    
    globs.pipelineLayout = new PipelineLayout(
        globs.ctx,
        globs.pushConstants,
        {
            globs.descriptorSetLayout,
            nullptr,
            nullptr
        },
        "globs.pipelineLayout"
    );
    
    globs.pipeline = (new GraphicsPipeline(
        globs.ctx,
        globs.pipelineLayout,
        globs.vertexManager->layout,
        globs.framebuffer,
        "main pipeline"
    ))
    ->set(ShaderManager::load("shaders/main.vert"))
    ->set(ShaderManager::load("shaders/main.frag"));
    
    globs.skymappipeline = globs.pipeline->clone("skybox pipeline")
        ->set(ShaderManager::load("shaders/sky.vert"))
        ->set(ShaderManager::load("shaders/sky.frag"));

    globs.skyboxMesh = Meshes::getFromGLTF(
        globs.vertexManager,
        gltf::parse("assets/skybox.glb")
    )[0];


    globs.descriptorSetFactory = new DescriptorSetFactory(
        globs.ctx,
        "per mesh dsf",
        DESCRIPTOR_SET_BINDING_POINT,
        globs.pipelineLayout
    );
    
    globs.descriptorSet = globs.descriptorSetFactory->make();
    
    globs.uniforms = new Uniforms(globs.ctx, "shaders/uniforms.txt");
    
    //uniform initialization
    globs.Environmap = ImageManager::loadCube({
        "assets/roomenvmap0.jpg",
        "assets/roomenvmap1.jpg",
        "assets/roomenvmap2.jpg",
        "assets/roomenvmap3.jpg",
        "assets/roomenvmap4.jpg",
        "assets/roomenvmap5.jpg"
        });

    globs.skyBoxImage = ImageManager::loadCube({
        "assets/nebula1_0.jpg",
        "assets/nebula1_1.jpg",
        "assets/nebula1_2.jpg",
        "assets/nebula1_3.jpg",
        "assets/nebula1_4.jpg",
        "assets/nebula1_5.jpg"
        });

    gltf::GLTFScene scene = gltf::parse("assets/room.glb");
    globs.allLights = new LightCollection(scene,globs.uniforms->getDefine("MAX_LIGHTS"));
    globs.allMeshes = Meshes::getFromGLTF(globs.vertexManager, scene );
     

    globs.vertexManager->pushToGPU();
    ImageManager::pushToGPU();
    
    #ifdef START_UNLOCKED
        globs.mouseLook=false;
    #else
        SDL_SetRelativeMouseMode(SDL_TRUE);
        globs.mouseLook=true;
    #endif
}