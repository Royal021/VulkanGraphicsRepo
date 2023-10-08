#include "vkhelpers.h"
#include "Descriptors.h"
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
    
    /// the rendering context
    VulkanContext* ctx;
    
    /// the framebuffer associated with the window
    Framebuffer* framebuffer;
    
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

    Image* skyBoxImage;
    Image* Environmap;
    Mesh* skyboxMesh;
    

    GraphicsPipeline* grassPipeline;

    float time = 0.0f;
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
    
    /// the default camera
    Camera camera{
        math2801::vec3{-0.277049,0.871309,3.330611},
        math2801::vec3{-0.166372,0.850771,2.336963},
        math2801::vec3{0.002274,0.999789,-0.020413},
        35.0f,
        1.0f,
        0.01f,
        1000.0f
    };
    
    /// collection of all meshes
    std::vector<Mesh*> allMeshes;
    
    /// collection of all lights
    LightCollection* allLights;



    
    /// true if program is in mouselook mode
    bool mouseLook;
};
