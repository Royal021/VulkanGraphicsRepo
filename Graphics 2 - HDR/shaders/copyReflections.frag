#version 450 core
#extension GL_GOOGLE_include_directive : enable

#include "../importantConstants.h"

layout(location=0) in vec2 texcoord;
layout(location=0) out vec4 color;
layout(set=0,binding=BASE_TEXTURE_SAMPLER_SLOT) uniform sampler texSampler;
layout(set=0,binding=BASE_TEXTURE_SLOT) uniform texture2DArray baseColorTexture;

void main(){
    vec4 c = texture(
        sampler2DArray(
            baseColorTexture,texSampler
        ),
        vec3(texcoord,0)
    );
    color = c;
}