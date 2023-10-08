#version 450 core

#extension GL_GOOGLE_include_directive : enable

#include "../importantConstants.h"
#include "pushconstants.txt"
#include "uniforms.txt"

layout(location=POSITION_SLOT) in vec3 position;
layout(location=0) out vec3 v_worldpos;

void main(){
    vec4 p = vec4(position,1.0);
    p = p * worldMatrix;
    v_worldpos = p.xyz;
    p = p * viewProjMatrix;
    gl_Position = p;
}