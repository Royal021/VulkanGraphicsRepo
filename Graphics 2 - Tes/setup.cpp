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
        ->set(VkPipelineInputAssemblyStateCreateInfo{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .topology = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST,
            .primitiveRestartEnable = 0
            })
        ->set(VkPipelineTessellationStateCreateInfo{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .patchControlPoints = 3
            })
        ->set(ShaderManager::load("shaders/main.vert"))
        ->set(ShaderManager::load("shaders/main.tesc"))
        ->set(ShaderManager::load("shaders/main.tese"))
        ->set(ShaderManager::load("shaders/main.frag"))
     /*   ->set(VkPipelineRasterizationStateCreateInfo{
     .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
     .pNext = nullptr,
     .flags = 0,
     .depthClampEnable = 0,
     .rasterizerDiscardEnable = 0,
     .polygonMode = VK_POLYGON_MODE_LINE,
     .cullMode = 0,
     .frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
     .depthBiasEnable = 0,
     .depthBiasConstantFactor = 0,
     .depthBiasClamp = 0,
     .depthBiasSlopeFactor = 0,
     .lineWidth = 1.0f
            })*/
        ;


    globs.skypipeline = (new GraphicsPipeline(
        globs.ctx, globs.pipelineLayout,
        globs.vertexManager->layout,
        globs.framebuffer, "skypipe"))
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

   /* globs.camera.lookAt(
        vec3(0.625081, 0.217267, 1.197354),
        vec3(0.126577, -0.078765, 0.382578),
        vec3(-0.154498, 0.955178, -0.252517)
    );*/

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
