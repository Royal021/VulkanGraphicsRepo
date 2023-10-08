 
#include <SDL.h>
#include "Globals.h"
#include "consoleoutput.h"

using namespace math2801;
   
void update(Globals& globs, float elapsed)
{
    float speed=1.0;
    if( globs.keys.contains(SDLK_LSHIFT)) speed *= 4.0f;
    if( globs.keys.contains(SDLK_w) )     globs.camera.strafeNoUpDown(0,0,speed*elapsed);
    if( globs.keys.contains(SDLK_s) )     globs.camera.strafeNoUpDown(0,0,-speed*elapsed);
    if( globs.keys.contains(SDLK_a) )     globs.camera.strafeNoUpDown(-speed*elapsed,0,0);
    if( globs.keys.contains(SDLK_d) )     globs.camera.strafeNoUpDown(speed*elapsed,0,0);
    if( globs.keys.contains(SDLK_r) )     globs.camera.strafe(0,0.1f*speed*elapsed,0);
    if( globs.keys.contains(SDLK_f) )     globs.camera.strafe(0,-0.1f*speed*elapsed,0);
    if( globs.keys.contains(SDLK_q) )     globs.camera.turn(0.5f*speed*elapsed);
    if( globs.keys.contains(SDLK_e) )     globs.camera.turn(-0.5f*speed*elapsed);
}

void handleEvents(Globals& globs)
{
    SDL_Event ev;
    while(true){
        bool eventOccurred = SDL_PollEvent(&(ev));
        if(! eventOccurred )
            break;
        if(ev.type == SDL_QUIT)
            globs.keepLooping=false;
        if(ev.type == SDL_KEYDOWN){
            globs.keys.insert(ev.key.keysym.sym);
            if(ev.key.keysym.sym == SDLK_ESCAPE)
                globs.keepLooping=false;
            if(ev.key.keysym.sym == SDLK_RETURN){
                print("eye:",globs.camera.eye);
                print("coi:",globs.camera.eye+globs.camera.look);
                print("up:",globs.camera.up);
            }
            if(ev.key.keysym.sym == SDLK_TAB){
                globs.mouseLook = ! globs.mouseLook;
                if(globs.mouseLook)
                     SDL_SetRelativeMouseMode(SDL_TRUE);
                else
                     SDL_SetRelativeMouseMode(SDL_FALSE);
            }
            if(ev.key.keysym.sym == SDLK_F1){
                globs.ctx->screenshot(0,"screenshot.png");
                print("Wrote screenshot.png");
            }
            if (ev.key.keysym.sym == SDLK_1) {           
                globs.focD += 0.05f; 
            }
            if (ev.key.keysym.sym == SDLK_2) {
                globs.focD -= 0.05f;
            }
        }
        if(ev.type == SDL_KEYUP){
            globs.keys.erase(ev.key.keysym.sym);
        }
        if(ev.type == SDL_MOUSEBUTTONDOWN){
        }
        if(ev.type == SDL_MOUSEBUTTONUP){
        }
        if(ev.type == SDL_MOUSEMOTION){
            if(globs.mouseLook){
                globs.camera.turn(float( -0.01*ev.motion.xrel) );
                globs.camera.tilt(float( -0.01*ev.motion.yrel) );
            }
        }
    }
}
    
