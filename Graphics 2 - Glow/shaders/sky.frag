#version 450 core

#extension GL_GOOGLE_include_directive : enable

#include "../importantConstants.h"
#include "pushconstants.txt"
#include "uniforms.txt"

layout(location=0) in vec2 texcoord;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 worldPos;
layout(location=3) in vec4 tangent;
layout(location=4) in vec2 texcoord2;
layout(location=5) in vec3 objPos;

layout(location=0) out vec4 color;
layout(location=1) out vec4 glow;

layout(set=0,binding=BASE_TEXTURE_SAMPLER_SLOT) uniform sampler texSampler;
layout(set=0,binding=BASE_TEXTURE_SLOT) uniform texture2DArray baseColorTexture;
layout(set=0,binding=EMISSIVE_TEXTURE_SLOT) uniform texture2DArray emissiveTexture;
layout(set=0,binding=NORMAL_TEXTURE_SLOT) uniform texture2DArray normalTexture;
layout(set=0,binding=METALLICROUGHNESS_TEXTURE_SLOT) uniform texture2DArray metallicRoughnessTexture;
layout(set=0,binding=SKYBOX_TEXTURE_SLOT) uniform textureCube skybox;


void main(){
    vec4 c = texture( samplerCube(skybox,texSampler), objPos);
    color = c;
    glow = vec4 (0.0f,0.0f,0.0f,1.0f);
}
