#include "vkhelpers.h"
#include "CommandBuffer.h"
#include "Pipeline.h"
#include "utils.h"
#include "timeutil.h"
#include "ShaderManager.h"
#include "VertexManager.h"
#include "Meshes.h"
#include "PushConstants.h"
#include "Descriptors.h"
#include "Images.h"
#include "ImageManager.h"
#include "Samplers.h"
#include "Uniforms.h"
#include "Camera.h"
#include "math2801.h"
#include "gltf.h"
#include "Light.h"
#include "Framebuffer.h"
#include "imageencode.h"
#include "CleanupManager.h"
#include "consoleoutput.h"
#include "importantConstants.h"
//for screenshot
#include "imagedecode.h"
#include <set>
#include <fstream>
#include <SDL.h>

#include "Globals.h"
void setup(Globals& g);
void draw(Globals& g);
void update(Globals& globs, float elapsed);
void handleEvents(Globals& globs);
void mainloop(Globals& globs);

using namespace math2801;


int main(int , char** )
{
    Globals globs{};

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Rect r;
    SDL_GetDisplayBounds( 0 , &(r) );
    globs.height = int(r.h/2.0);
    globs.width = globs.height;
    SDL_Window* win = SDL_CreateWindow("ETGG",
        10,10, globs.width, globs.height,
        SDL_WINDOW_VULKAN );

    if( !win ){
        std::cout << "Could not create window\n";
        return 1;
    }

    VkPhysicalDeviceFeatures featuresToEnable{};
    featuresToEnable.samplerAnisotropy=VK_TRUE;
    featuresToEnable.fillModeNonSolid=VK_TRUE;
    featuresToEnable.tessellationShader = VK_TRUE;
    globs.ctx = new VulkanContext(win=win,featuresToEnable,1);

    CommandBuffer::initialize(globs.ctx);
    ImageManager::initialize(globs.ctx);
    ShaderManager::initialize(globs.ctx);
    Framebuffer::initialize(globs.ctx);
    Images::initialize(globs.ctx);
    Samplers::initialize(globs.ctx);

    setup(globs);

    mainloop(globs);

    CleanupManager::cleanupEverything();
    globs.ctx->cleanup();

    SDL_Quit();
    return 0;
}

void mainloop(Globals& globs)
{
    float DESIRED_FRAMES_PER_SEC = 60;
    float DESIRED_SEC_PER_FRAME = 1/DESIRED_FRAMES_PER_SEC;
    float QUANTUM = 0.005f;     //5 msec
    float accumulated = 0.0f;
    double last=timeutil::time_sec();
    while(globs.keepLooping){
        double now = timeutil::time_sec();
        float elapsed = float(now-last);
        last=now;
        accumulated += elapsed;
        handleEvents(globs);
        while(accumulated >= QUANTUM){
            update(globs,QUANTUM);
            accumulated -= QUANTUM;
        }
        draw(globs);
        double end = timeutil::time_sec();
        float frameTime = float(end-now);
        float leftover = DESIRED_SEC_PER_FRAME - frameTime;
        if(leftover > 0)
            timeutil::sleep(leftover);
    }
}

