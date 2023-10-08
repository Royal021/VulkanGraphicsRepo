#version 450 core

#extension GL_GOOGLE_include_directive : enable

#include "../importantConstants.h"
#include "pushconstants.txt"
#include "uniforms.txt"

layout(vertices=3) out;

layout(location=0) in vec2 texcoord[];
layout(location=1) in vec2 texcoord2[];
layout(location=2) in vec3 normal[];
layout(location=3) in vec3 worldpos[];
layout(location=4) in vec4 tangent[];

layout(location=0) out vec2 t_texcoord[];
layout(location=1) out vec2 t_texcoord2[];
layout(location=2) out vec3 t_normal[];
layout(location=3) out vec3 t_worldpos[];
layout(location=4) out vec4 t_tangent[];

void main(){
    gl_TessLevelOuter[0] = tessLevel;
    gl_TessLevelOuter[1] = tessLevel;
    gl_TessLevelOuter[2] = tessLevel;
    gl_TessLevelInner[0] = tessLevel;
    t_texcoord[gl_InvocationID]  = texcoord[gl_InvocationID] ;
    t_texcoord2[gl_InvocationID] = texcoord2[gl_InvocationID];
    t_normal[gl_InvocationID]    = normal[gl_InvocationID]   ;
    t_worldpos[gl_InvocationID]  = worldpos[gl_InvocationID] ;
    t_tangent[gl_InvocationID]   = tangent[gl_InvocationID]  ;
}