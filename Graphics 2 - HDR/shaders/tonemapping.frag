#version 450 core
#extension GL_GOOGLE_include_directive : enable
#include "../importantConstants.h"
layout(location=0) in vec2 texcoord;
layout(location=0) out vec4 color;
layout(set=0,binding=BASE_TEXTURE_SAMPLER_SLOT) uniform sampler texSampler;
layout(set=0,binding=BASE_TEXTURE_SLOT) uniform texture2DArray baseColorTexture;

void main(){
    vec3 avg = texture(
                sampler2DArray(baseColorTexture,texSampler),
                vec3(texcoord,0),
                999 ).rgb;
    vec3 xyY = texture( sampler2DArray(baseColorTexture,texSampler),
                vec3(texcoord,0) ).rgb;

    float mn = avg.b-0.25;
    float mx = avg.b+0.25;
    float Y = smoothstep(mn,mx,xyY.b);
    float x = xyY.r;
    float y = xyY.g;

    float X = (Y*x)/y;
    float Z = (Y*(1.0-x-y))/y;

    float r = 3.2404542*X + -1.5371385*Y + -0.4985314*Z ;
    float g = -0.969266*X + 1.8760108*Y + 0.0415560*Z ;
    float b = 0.0556434*X + -0.204259*Y + 1.0572252*Z ;

    color.rgb = vec3(r,g,b);
    color.a=1.0;
    return;
}