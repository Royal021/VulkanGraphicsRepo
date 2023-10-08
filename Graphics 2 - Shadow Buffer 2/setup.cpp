#include "vkhelpers.h"
#include "Globals.h"
#include "ShaderManager.h"
#include "importantConstants.h"
#include "Uniforms.h"
#include "ImageManager.h"
#include "gltf.h"
#include "GraphicsPipeline.h"
#include <SDL.h>
#include "Samplers.h"

using namespace math2801;
  
void setup(Globals& globs)
{
    globs.keepLooping=true;
    globs.framebuffer = new Framebuffer();
    globs.uniforms = new Uniforms(globs.ctx, "shaders/uniforms.txt");
    globs.shadowBuffer = new Framebuffer(512, 512,
        globs.uniforms->getDefine("MAX_LIGHTS"),
        VK_FORMAT_R32_SFLOAT, "shadowbuffer"
    );


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
            {.type = VK_DESCRIPTOR_TYPE_SAMPLER,           .slot = NEAREST_SAMPLER_SLOT },
            { .type=VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,     .slot=BASE_TEXTURE_SLOT         },
            { .type=VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,     .slot=EMISSIVE_TEXTURE_SLOT     },
            { .type=VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,    .slot=UNIFORM_BUFFER_SLOT       },
            {.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,    .slot = NORMAL_TEXTURE_SLOT     },
            {.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,    .slot = METALLICROUGHNESS_TEXTURE_SLOT    },
            {.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,   .slot = ENVMAP_TEXTURE_SLOT  },
            {.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,   .slot = SHADOWBUFFER_SLOT  }

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

    globs.shadowPipeline = (new GraphicsPipeline(
        globs.ctx,
        globs.pipelineLayout,
        globs.vertexManager->layout,
        globs.shadowBuffer,
        "shadow pipeline"
    ))
        ->set(globs.shadowBuffer->singleLayerRenderPassClear)
        ->set(VkPipelineRasterizationStateCreateInfo{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .depthClampEnable = 0,
            .rasterizerDiscardEnable = 0,
            .polygonMode = VK_POLYGON_MODE_FILL,
            .cullMode = VK_CULL_MODE_BACK_BIT,
            .frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
            .depthBiasEnable = 0,
            .depthBiasConstantFactor = 0,
            .depthBiasClamp = 0,
            .depthBiasSlopeFactor = 0,
            .lineWidth = 1.0f
            })
        ->set(ShaderManager::load("shaders/shadow.vert"))
        ->set(ShaderManager::load("shaders/shadow.frag"));

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

    gltf::GLTFScene scene = gltf::parse("assets/kitchen.glb");
    globs.allLights = new LightCollection(scene,globs.uniforms->getDefine("MAX_LIGHTS"));
    globs.allMeshes = Meshes::getFromGLTF(globs.vertexManager, scene );
     
    //vec3 lightPos = globs.allLights->lightPositionAndDirectionalFlag[0].xyz();
    //vec3 lightDir = globs.allLights->spotDirection[0].xyz();

   //getting light cameras
    for (unsigned i = 0; i < (unsigned)globs.allLights->lightPositionAndDirectionalFlag.size(); ++i) 
    {
        vec3 lightPos = globs.allLights->lightPositionAndDirectionalFlag[i].xyz();
        vec3 lightDir = globs.allLights->spotDirection[i].xyz();
        vec3 lightUp;
        if (std::abs(dot(lightDir, vec3(0, 1, 0))) > 0.8)
            lightUp = vec3(1, 0, 0);
        else
            lightUp = vec3(0, 1, 0);

        globs.lightCameras.push_back(Camera(
            lightPos, lightPos + lightDir, lightUp,
            float(std::acos(globs.allLights->cosSpotAngles[i].y) / 3.14159265358797323 * 180),
            1.0f,
            0.01f,      //hither
            20.0f       //yon
        ));
    }
    ////c
    for (auto& cam : globs.lightCameras) {
        globs.light_eyePos.push_back(math2801::vec4(cam.eye, 1.0f));
        globs.light_viewProjMatrix.push_back(cam.viewProjMatrix);
        globs.light_hitherYon.push_back(math2801::vec4(
            cam.hither, cam.yon, cam.yon - cam.hither, 0.0));
    }

    globs.descriptorSet->setSlot(NEAREST_SAMPLER_SLOT, Samplers::nearestSampler);
    globs.vertexManager->pushToGPU();
    ImageManager::pushToGPU();
    
    #ifdef START_UNLOCKED
        globs.mouseLook=false;
    #else
        SDL_SetRelativeMouseMode(SDL_TRUE);
        globs.mouseLook=true;
    #endif
}
