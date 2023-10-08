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

layout(location=0) out vec4 color;

layout(set=0,binding=BASE_TEXTURE_SAMPLER_SLOT) uniform sampler texSampler;
layout(set=0,binding=BASE_TEXTURE_SLOT) uniform texture2DArray baseColorTexture;
layout(set=0,binding=EMISSIVE_TEXTURE_SLOT) uniform texture2DArray emissiveTexture;
layout(set=0,binding=NORMAL_TEXTURE_SLOT) uniform texture2DArray normalTexture;

#define AMBIENT_ABOVE vec3(0.3,0.3,0.3)
#define AMBIENT_BELOW vec3(0.1,0.1,0.1)

// c=Base object color
// i=index of light
// N=Normal
// V=Vector to viewer
// dp = diffuse percentage (output)
// sp = specular percentage (output)
void computeLightContribution(vec3 c, int i, vec3 N, vec3 V, out vec3 diffuse, out vec3 specular)
{
    vec3 lightPosition = lightPositionAndDirectionalFlag[i].xyz;
    float positional = lightPositionAndDirectionalFlag[i].w;
    vec3 spotDir = spotDirection[i].xyz;
    float cosSpotInnerAngle = cosSpotAngles[i].x;
    float cosSpotOuterAngle = cosSpotAngles[i].y;
    vec3 lightColor = lightColorAndIntensity[i].xyz;
    float intensity = lightColorAndIntensity[i].w;
    
    vec3 L = lightPosition - worldPos*positional;
    float D = length(L);
    L /= D;
    float dp = dot(N,L);
    dp = clamp(dp,0.0,1.0);
    
    vec3 R = reflect(-L,N);
    float sp = sign(dp) * dot(V,R);
    sp = clamp(sp,0.0,1.0);
    sp = pow(sp,16.0);
    
    float A = 1.0/(attenuation[0] + D*(attenuation[1] + D*attenuation[2]));
    A = clamp(A,0.0,1.0);
    
    dp *= A;
    sp *= A;
    
    float spotdot = dot(-L,spotDir);
    float SA = smoothstep( cosSpotOuterAngle, cosSpotInnerAngle, spotdot );
    
    dp *= SA;
    sp *= SA;

    diffuse = dp * c * intensity * lightColor;
    specular = sp * intensity * lightColor;
    
}
   
vec3 doBumpMapping(vec3 b, vec3 N)
{
    if( tangent.w == 0.0 )
        return N;

    N = normalize(N);

    vec3 T = tangent.xyz;
    T = T - dot(T, N) * N;
    T = normalize(T);
    vec3 B = cross( N, T);
    B = B * tangent.w;
    vec3 beta = 2.0 * (b - vec3(0.5));
    beta.xy = normalFactor * beta.xy;
    N = beta * mat3(T.x, B.x, N.x, T.y, B.y, N.y, T.z, B.z, N.z);

    
    return N;       //bump mapped normal
}

void main(){
     
    vec4 c = texture( sampler2DArray(baseColorTexture,texSampler),
                      vec3(texcoord,animationFrame) );
    c = c * baseColorFactor;
    
    vec3 b = texture( sampler2DArray(normalTexture, texSampler),
                    vec3(texcoord2,animationFrame) ).xyz;

    vec3 N = normal;
    N = doBumpMapping(b.xyz, N);

    N = (vec4(N,0.0) * worldMatrix).xyz;
    N = normalize(N);

    float mappedY = 0.5 * (N.y+1.0);
    vec3 ambient = mix( AMBIENT_BELOW, AMBIENT_ABOVE, mappedY );
    
    vec3 V = normalize(eyePos-worldPos);
    
    vec3 totaldp = vec3(0.0);
    vec3 totalsp = vec3(0.0);
    
    for(int i=0;i<MAX_LIGHTS;++i){
        vec3 dp;
        vec3 sp;
        computeLightContribution(c.rgb,i,N,V,dp,sp);
        
        totaldp += dp;
        totalsp += sp;
    }
   
    c.rgb = c.rgb * (ambient + totaldp) + totalsp;
    c.rgb = clamp(c.rgb, vec3(0.0), vec3(1.0) );
    vec4 e = texture( sampler2DArray(emissiveTexture,texSampler),
                      vec3(texcoord,0.0) );
    c.rgb += e.rgb * emissiveFactor.rgb;
    if (doingShadow!= 0)
    {
    
     color = vec4((c.rgb * (ambient + totaldp) + totalsp),1);
     return;
     }
    color = c;
}
