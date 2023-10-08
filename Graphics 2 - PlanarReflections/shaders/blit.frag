#version 450 core
#extension GL_GOOGLE_include_directive : enable

#include "../importantConstants.h"
#include "uniforms.txt"

layout(location=0) in vec2 texcoord;
layout(location=0) out vec4 color;
layout(set=0,binding=BASE_TEXTURE_SAMPLER_SLOT)
uniform sampler texSampler;

layout(set=0,binding=NEAREST_SAMPLER_SLOT)
uniform sampler nearestSampler;

layout(set=0,binding=BASE_TEXTURE_SLOT)
uniform texture2DArray baseColorTexture;

layout(set=0,binding=DEPTH_TEXTURE_SLOT)
uniform texture2DArray depthTexture;


void main(){
    vec4 sharp = texture(
        sampler2DArray(
            baseColorTexture,texSampler
        ),
        vec3(texcoord,0)
    );
    vec4 blurry = texture(
        sampler2DArray(
            baseColorTexture,texSampler
        ),
        vec3(texcoord,1)
    );
    float d = texture( sampler2DArray(depthTexture,nearestSampler),
                  vec3(texcoord,0) ).r;
    
    float P = projMatrix[2][2];
    float Q = projMatrix[2][3]; //column major indexing!
    float depth = Q/(d+P); //true depth -> negated
    float delta = abs(depth-focalDistance);  //focalDistance=uniform
    float mixFactor = smoothstep( 0.0, 2.5, delta ); //2.5=depth of field
    color = mix( sharp, blurry, mixFactor );
    //color.rgb = vec3(d);
    color.a = 1.0;

}
    
