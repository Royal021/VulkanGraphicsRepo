#version 450 core
#extension GL_GOOGLE_include_directive : enable
layout(location=0) in vec2 texcoord;
layout(location=1) in float lifeLeft;
layout(location=0) out vec4 color;
layout(set=0,binding=0) uniform sampler texSampler;
layout(set=0,binding=1) uniform texture2DArray baseColorTexture;
#include "pushconstants.txt"
#include "uniforms.txt"
void main(){
    vec4 c = texture(
        sampler2DArray(baseColorTexture, texSampler),
        vec3(texcoord,0.0)
    );

    color = c;
    color.a *= smoothstep(0.0,0.5,lifeLeft);
}