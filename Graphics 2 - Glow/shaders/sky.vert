#version 450 core

#extension GL_GOOGLE_include_directive : enable

#include "../importantConstants.h"
#include "pushconstants.txt"
#include "uniforms.txt"

layout(location=POSITION_SLOT) in vec3 position;
layout(location=TEXCOORD_SLOT) in vec2 texcoord;
layout(location=NORMAL_SLOT) in vec3 normal;
layout(location=TANGENT_SLOT) in vec4 tangent;
layout(location=TEXCOORD2_SLOT) in vec2 texcoord2;


layout(location=0) out vec2 v_texcoord;
layout(location=1) out vec3 v_normal;
layout(location=2) out vec3 v_worldpos;
layout(location=3) out vec4 v_tangent;
layout(location=4) out vec2 v_texcoord2;
layout(location=5) out vec3 objPos;

void main(){
    objPos = position;
    vec3 p = position;
    p += eyePos;
    vec4 k = vec4(p,1.0);
    k = k * viewProjMatrix;
    k.z = k.w;
    gl_Position = k;
    v_texcoord = texcoord;
    v_normal = normal;
    v_tangent = tangent;
    v_texcoord2 = texcoord2;

}
