#include "vkhelpers.h"
#include "Descriptors.h"
#include "BlitSquare.h"
#include "Camera.h"
#include "PushConstants.h"
#include "GraphicsPipeline.h"
#include "VertexManager.h"
#include "Framebuffer.h"
#include "Meshes.h"
#include "Light.h"
#include <vector>
#include <set>

struct Globals{
    
    /// width of the window
    int width;
    
    /// height of the window
    int height;
    
    /// focal dist
    float focD = 1.0f;
    
    /// the rendering context
    VulkanContext* ctx;
    
    /// the framebuffer associated with the window
    Framebuffer* framebuffer;
    Framebuffer* offscreen;
    
    /// default vertex manager
    VertexManager* vertexManager;
    
    /// true as long as the program should keep running
    bool keepLooping;
    
    /// set of keys that are currently pressed
    std::set<int> keys;
    
    /// push constants
    PushConstants* pushConstants;
    
    /// the default graphics pipeline
    GraphicsPipeline* pipeline;
    GraphicsPipeline* skymappipeline;
    GraphicsPipeline* floorPipeline1;
    GraphicsPipeline* reflectedObjectsPipeline;
    GraphicsPipeline* floorPipeline2;
    GraphicsPipeline* blitPipe;

    Image* skyBoxImage;
    Image* Environmap;
    Mesh* skyboxMesh;
    
    /// the pipeline layout
    PipelineLayout* pipelineLayout;
    
    /// layout of the descriptor set
    DescriptorSetLayout* descriptorSetLayout;
    
    /// factory for making descriptor sets
    DescriptorSetFactory* descriptorSetFactory;
    
    /// the active descriptor set
    DescriptorSet* descriptorSet;

    /// manager for uniforms
    Uniforms* uniforms;

    /// reflection
    math2801::mat4 reflectionMatrix;
    math2801::vec4 reflectionPlane;

    
    /// the default camera
    Camera camera{
        math2801::vec3{-0.92,1.43,1.88},
        math2801::vec3{-1.77,1.25,1.38},
        math2801::vec3{0,1,0},
        35.0f,
        1.0f,
        0.01f,
        1000.0f
    };
    
    /// collection of all meshes
    std::vector<Mesh*> allMeshes;
    
    /// collection of all lights
    LightCollection* allLights;

    //blitsquare
    BlitSquare* blitSquare;



    
    /// true if program is in mouselook mode
    bool mouseLook;
};
