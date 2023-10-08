#version 450 core
#extension GL_GOOGLE_include_directive : enable
layout(location=0) in vec2 texcoord;
layout(location=0) out vec4 color;
layout(set=0,binding=0) uniform sampler texSampler;
layout(set=0,binding=1) uniform texture2DArray baseColorTexture;
#include "pushconstants.txt"
#include "uniforms.txt"
#include "perlin.h"
void main(){
   
    vec2 texcoor = vec2(texcoord.x, 1-texcoord.y);
    vec3 v = vec3(texcoor.xy * 8.0,time*2.0);
v.y += time * 8.0;
float n = noise(v);
n += 0.5 * noise(2.0*v);
n += 0.25 * noise(4.0*v);
n = 0.5*(n + 1.0);
float s = smoothstep( 0.0, texcoor.y, n*0.75 );
s=smoothstep(0.0,1.0,s);
color = texture(  sampler2DArray(baseColorTexture,texSampler), vec3( s, 0.5, 0 ) );
}