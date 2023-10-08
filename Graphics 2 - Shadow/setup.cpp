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
    globs.vertexManager = new VertexManager(
        globs.ctx,
        {
            {.format = VK_FORMAT_R32G32B32_SFLOAT,   .rate = VK_VERTEX_INPUT_RATE_VERTEX },  //position
            {.format = VK_FORMAT_R32G32_SFLOAT,      .rate = VK_VERTEX_INPUT_RATE_VERTEX },  //texcoord
            {.format = VK_FORMAT_R32G32B32_SFLOAT,   .rate = VK_VERTEX_INPUT_RATE_VERTEX },  //normal
            {.format = VK_FORMAT_R32G32B32A32_SFLOAT,.rate = VK_VERTEX_INPUT_RATE_VERTEX },   //tangent
            {.format = VK_FORMAT_R32G32_SFLOAT,      .rate = VK_VERTEX_INPUT_RATE_VERTEX } //TEX2
        }
    );

    globs.pushConstants = new PushConstants("shaders/pushconstants.txt");

    globs.descriptorSetLayout = new DescriptorSetLayout(
        globs.ctx,
        {
            {.type = VK_DESCRIPTOR_TYPE_SAMPLER,           .slot = BASE_TEXTURE_SAMPLER_SLOT },
            {.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,     .slot = BASE_TEXTURE_SLOT         },
            {.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,     .slot = EMISSIVE_TEXTURE_SLOT     },
            {.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,    .slot = UNIFORM_BUFFER_SLOT       },
            {.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,     .slot = NORMAL_TEXTURE_SLOT       }

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

    globs.descriptorSetFactory = new DescriptorSetFactory(
        globs.ctx,
        "per mesh dsf",
        DESCRIPTOR_SET_BINDING_POINT,
        globs.pipelineLayout
    );

    globs.descriptorSet = globs.descriptorSetFactory->make();

    globs.framebuffer = new Framebuffer();

    //pipelines
    //Everything non floor or shadow
    globs.pipelineNonFloor = (new GraphicsPipeline(
        globs.ctx,
        globs.pipelineLayout,
        globs.vertexManager->layout,
        globs.framebuffer,
        "main pipeline"
    ))
        ->set(ShaderManager::load("shaders/main.vert"))
        ->set(ShaderManager::load("shaders/main.frag"));

    //Floor
    globs.pipelineFloor = globs.pipelineNonFloor->clone("floor pipe")
        ->set(true, true, true, VK_COMPARE_OP_ALWAYS, 1,
            VK_STENCIL_OP_KEEP, VK_STENCIL_OP_KEEP,
            VK_STENCIL_OP_REPLACE);
    //Shadow
    globs.pipelineShadow = globs.pipelineNonFloor->clone("shadow pipe")
        ->set(false, false, true, VK_COMPARE_OP_EQUAL, 1,
            VK_STENCIL_OP_KEEP, VK_STENCIL_OP_KEEP,
            VK_STENCIL_OP_INCREMENT_AND_CLAMP)
        ->set(VK_BLEND_FACTOR_ZERO, VK_BLEND_FACTOR_ONE)
        ->set(ShaderManager::load("shaders/shadow.vert"))
        ->set(ShaderManager::load("shaders/shadow.frag"));

    //FloorShadow
    globs.pipelineFloorShadow = globs.pipelineNonFloor->clone(
        "shadow pipe"
    )->set(false, false, true, VK_COMPARE_OP_EQUAL, 2,
        VK_STENCIL_OP_KEEP, VK_STENCIL_OP_KEEP,
        VK_STENCIL_OP_KEEP);


    globs.uniforms = new Uniforms(globs.ctx, "shaders/uniforms.txt");

    gltf::GLTFScene scene = gltf::parse("assets/room3.glb");
    globs.allLights = new LightCollection(scene, globs.uniforms->getDefine("MAX_LIGHTS"));
    globs.allMeshes = Meshes::getFromGLTF(globs.vertexManager, scene);

    mat4 T = translation(-globs.allLights->lightPositionAndDirectionalFlag[0].xyz());
    mat4 T_1 = translation(globs.allLights->lightPositionAndDirectionalFlag[0].xyz());
    vec3 p(0, -0.3135f, 0);
    vec3 pt = (vec4(p, 1.0f) * T).xyz();
    float A = 0.0f;
    float B = 1.0f;
    float C = 0.0f;
    float D = -(A * pt.x + B * pt.y + C * pt.z);

    globs.flattenMatrix = mat4(
        -D, 0, 0, A,
        0, -D, 0, B,
        0, 0, -D, C,
        0, 0, 0, 0
    );

    globs.flattenMatrix = -(T * globs.flattenMatrix * T_1);

    globs.keepLooping = true;

    globs.vertexManager->pushToGPU();
    ImageManager::pushToGPU();

#ifdef START_UNLOCKED
    globs.mouseLook = false;
#else
    SDL_SetRelativeMouseMode(SDL_TRUE);
    globs.mouseLook = true;
#endif
}