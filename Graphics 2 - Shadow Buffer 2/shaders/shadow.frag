#version 450 core
#extension GL_GOOGLE_include_directive : enable
#include "uniforms.txt"
layout(location=0) in vec3 worldPos;
layout(location=0) out vec4 color;

void main(){
    float d = distance(eyePos, worldPos );
    color.rgb = vec3( (d - hitherYon[0]) / hitherYon[2] );
    color.a = 1.0;
}