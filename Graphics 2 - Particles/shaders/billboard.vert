#version 450 core

#extension GL_GOOGLE_include_directive : enable

#include "../importantConstants.h"
#include "pushconstants.txt"
#include "uniforms.txt"

layout(location=POSITION_SLOT) in vec3 indexInfo;
layout(location=TEXCOORD_SLOT) in vec2 texcoord;

layout(set=0,binding=BILLBOARD_TEXTURE_SLOT) uniform textureBuffer billboardPositions;

layout(location=0) out vec2 v_texcoord;
layout(location=1) out float lifeLeft;


void main(){
    
    vec2 size = indexInfo.yz;
    int idx = int(indexInfo.x);
    vec4 p = texelFetch( billboardPositions, gl_InstanceIndex*BATCH_SIZE + idx );
    
    //p holds center of billboard
    //vec4 p = texelFetch( billboardPositions, gl_InstanceIndex );
    lifeLeft=p.w;
    p.w = 1.0;

    //put in world space
    p = p * worldMatrix;

    p = p * viewMatrix;
    p.xy += size * (2.0 * texcoord - vec2(1.0));

 


    p = p * projMatrix;

    gl_Position = p;
    v_texcoord = texcoord;
}